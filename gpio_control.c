#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definindo os pinos GPIO para os LEDs e buzzer
#define LED_VERMELHO_PIN 13
#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define BUZZER_PIN 21

// Função para configurar os pinos
void setup_gpio() {
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);

    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

// Função para acionar o buzzer
void buzzer_on() {
    gpio_put(BUZZER_PIN, 1);  // Aciona o buzzer
    sleep_ms(2000);            // Espera 2 segundos
    gpio_put(BUZZER_PIN, 0);   // Desliga o buzzer
}

// Função para desligar todos os LEDs
void desligar_leds() {
    gpio_put(LED_VERMELHO_PIN, 0);
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 0);
}

// Função para acionar LEDs de acordo com o comando
void acionar_led(char comando) {
    desligar_leds();  // Desliga todos os LEDs antes de acionar o novo

    switch (comando) {
        case 'V':  // Ligar LED verde
            gpio_put(LED_VERDE_PIN, 1);
            break;
        case 'A':  // Ligar LED azul
            gpio_put(LED_AZUL_PIN, 1);
            break;
        case 'R':  // Ligar LED vermelho
            gpio_put(LED_VERMELHO_PIN, 1);
            break;
        case 'W':  // Ligar todos os LEDs (branco)
            gpio_put(LED_VERMELHO_PIN, 1);
            gpio_put(LED_VERDE_PIN, 1);
            gpio_put(LED_AZUL_PIN, 1);
            break;
        case 'D':  // Desligar todos os LEDs
            desligar_leds();
            break;
        default:
            break;
    }
}

int main() {
    stdio_init_all();  // Inicializa comunicação serial (UART)
    setup_gpio();      // Configura os pinos GPIO

    while (true) {
        char comando = getchar();  // Espera um comando via UART
        
        if (comando == 'B') {  // Comando para acionar o buzzer
            buzzer_on();
        } else {
            acionar_led(comando);  // Aciona LEDs conforme o comando
        }
    }

    return 0;
}