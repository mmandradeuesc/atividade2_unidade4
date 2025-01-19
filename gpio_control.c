#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

// Pinos GPIO para LEDs e buzzer
#define LED_VERMELHO_PIN 13
#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define BUZZER_PIN 21

// Configuração PWM (global)
uint slice_num;
uint channel_num;
static float current_clkdiv = 1.0f;
static uint16_t current_wrap = 25000 - 1;

// Funções para controlar os LEDs (sem alterações)
void setup_gpio() {
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
}

void desligar_leds() {
    gpio_put(LED_VERMELHO_PIN, 0);
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 0);
}

void acionar_led(char comando) {
    desligar_leds();
    switch (comando) {
        case 'V': 
            gpio_put(LED_VERDE_PIN, 1); 
            break;
        case 'A': 
            gpio_put(LED_AZUL_PIN, 1); 
            break;
        case 'R': 
            gpio_put(LED_VERMELHO_PIN, 1); 
            break;
        case 'W': 
            gpio_put(LED_VERMELHO_PIN, 1); 
            gpio_put(LED_VERDE_PIN, 1); 
            gpio_put(LED_AZUL_PIN, 1); 
            break;
        //case 'D':  desnecessário, default pega tudo; você pretende fazer algo diferente aqui?
        default: 
            desligar_leds(); 
            break;
    }
}

void acionamento(char* palavra){
    desligar_leds();
    //printf("entrou: %s\n", palavra);
    if (strcmp(palavra,"SOM") == 0) {
        buzzer_play_tone(1000, 2000); // Exemplo: 1kHz por 2 segundos
    } else if (strcmp(palavra,"VERDE") == 0){
        //printf("ENTROU NO VERDE");
        gpio_put(LED_VERDE_PIN, 1);
    } else if (strcmp(palavra,"AZUL") == 0){
        //printf("ENTROU NO AZUL");
        gpio_put(LED_AZUL_PIN, 1);
    } else if (strcmp(palavra,"VERMELHO") == 0){
        //printf("ENTROU NO VERMELHO");
        gpio_put(LED_VERMELHO_PIN, 1);
    } else if (strcmp(palavra,"RGB") == 0){
        gpio_put(LED_VERMELHO_PIN, 1); 
        gpio_put(LED_VERDE_PIN, 1); 
        gpio_put(LED_AZUL_PIN, 1);
    } else {
        desligar_leds();
    }
}

// Funções para controlar o buzzer (com as correções para PWM)
void buzzer_set_frequency(uint16_t frequency) {
    uint32_t clock_freq = 125000000;
    uint32_t wrap_value = clock_freq / (frequency * current_clkdiv) - 1;
    pwm_set_wrap(slice_num, wrap_value);
    current_wrap = wrap_value;
}

void buzzer_play_tone(uint16_t frequency, uint32_t duration_ms) {
    buzzer_set_frequency(frequency);
    pwm_set_chan_level(slice_num, channel_num, current_wrap / 6);
    sleep_ms(duration_ms);
    pwm_set_chan_level(slice_num, channel_num, 0);
}

int main() {
    stdio_init_all();
    setup_gpio();

    // Inicialização PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    channel_num = pwm_gpio_to_channel(BUZZER_PIN);
    pwm_set_clkdiv(slice_num, current_clkdiv);
    pwm_set_wrap(slice_num, current_wrap);
    pwm_set_enabled(slice_num, true);
    char comando;
    char palavra[50];
    uint8_t contador = 0;

    while (true) {
        comando = getchar();
        if (comando != PICO_ERROR_TIMEOUT){ //Entra no loop quando detecta um caractere inserido
            //printf("COMANDO: %c", comando);
            if (comando == '\r'){ //\r é o caractere enviado pelo monitor serial do PuTTY no final da palavra
                palavra[contador] = '\0';
                //printf("palavra: %s\n", palavra);
                acionamento(palavra); // Entra na lógica de que componente ativar (leds ou buzzer)
                memset(palavra, 0, sizeof(palavra)); //reinicia o buffer de palavra
                contador = 0; //reinicia o índice
                
                // if (comando == 'B') {
                //     buzzer_play_tone(1000, 2000); // Exemplo: 1kHz por 2 segundos
                // } else {
                //     acionar_led(comando);
                // }
            } else if ((contador < sizeof(palavra) - 1) && (comando >= 32 && comando <= 126)){ //verifica se o índice está ao final do vetor de caracteres palavra, e se o caractere enviado é um caractere ASCII válido, para capturar mais um caractere e introduzir em palavra
                palavra[contador++] = comando; 
            }
       }
    }
    return 0;
}
