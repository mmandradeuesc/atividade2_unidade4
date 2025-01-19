#include "pico/stdlib.h"
#include <stdio.h>

const uint led_pin_green = 11; // Especifica o led verde
const uint led_pin_blue = 12;  // led azul
const uint led_pin_red = 13;   // led vermelho
const uint buzzer_pin = 21;    // pino do buzzer

void init_gpio() {
    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
}

void turn_off_all() {
    gpio_put(led_pin_green, 0);
    gpio_put(led_pin_blue, 0);
    gpio_put(led_pin_red, 0);
    gpio_put(buzzer_pin, 0);
}

int main() {
    stdio_init_all();
    init_gpio();

    char command[10];

    while (1) {
        printf("Digite um comando: ");
        scanf("%s", command);

        if (strcmp(command, "red") == 0) {
            turn_off_all();
            gpio_put(led_pin_red, 1);
        } else if (strcmp(command, "blue") == 0) {
            turn_off_all();
            gpio_put(led_pin_blue, 1);
        } else if (strcmp(command, "green") == 0) {
            turn_off_all();
            gpio_put(led_pin_green, 1);
        } else if (strcmp(command, "buzzer") == 0) {
            turn_off_all();
            gpio_put(buzzer_pin, 1);
        } else if (strcmp(command, "stop") == 0) {
            turn_off_all();
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    return 0;
}