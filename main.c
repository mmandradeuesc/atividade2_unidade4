#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"


#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

void setup_gpio() {
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(BUZZER);

    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
    gpio_put(BUZZER, 0);
}

void setup_uart() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, false);
}

void handle_command(char command) {
    switch (command) {
        case 'V':
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);
            break;
        case 'A':
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 0);
            break;
        case 'R':
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 1);
            break;
        case 'W':
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            break;
        case 'O':
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);
            break;
        case 'B':
            gpio_put(BUZZER, 1);
            sleep_ms(2000);
            gpio_put(BUZZER, 0);
            break;
        case 'X':
            watchdog_reboot(0, 0, 0);
            break;
        default:
            break;
    }
}

int main() {
    setup_gpio();
    setup_uart();

    while (true) {
        if (uart_is_readable(UART_ID)) {
            char command = uart_getc(UART_ID);
            handle_command(command);
        }
        sleep_ms(100);
    }
}
