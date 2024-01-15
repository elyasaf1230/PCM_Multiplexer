#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Clock (Int)
#define PIN_CLK 2

#define PIN_IN1 10
#define PIN_IN2 11
#define PIN_IN3 12
#define PIN_IN4 13
int in_pins_arr[4] = { PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4 };
int current_in_pin = 0;

#define PIN_OUT 6

void gpio_callback(uint gpio, uint32_t events) {
    gpio_put(PIN_OUT, gpio_get(in_pins_arr[current_in_pin]));
    current_in_pin = ((current_in_pin + 1) % 4);
}

/********************* Only for tests **********************************/
#define PIN_CLK_OUT 3
#define PIN_OUT1 5

void mock()
{
    gpio_init(PIN_CLK_OUT);
    gpio_set_dir(PIN_CLK_OUT, true);

    gpio_init(PIN_OUT1);
    gpio_set_dir(PIN_OUT1, true);

    while (1) {
        uint8_t data = 0xff;
        for (int i = 0; i < 8; i++) {
            gpio_put(PIN_OUT1, (data & 0x1) == 1);
            data >>= 1;
            gpio_put(PIN_CLK_OUT, true);
            sleep_us(7);
            gpio_put(PIN_CLK_OUT, false);
            sleep_us(7);
        }
    }   
}
/*********************************************************************/

int main() {
    gpio_init(PIN_IN1);
    gpio_set_dir(PIN_IN1, false);
    gpio_init(PIN_IN2);
    gpio_set_dir(PIN_IN2, false);
    gpio_init(PIN_IN3);
    gpio_set_dir(PIN_IN3, false);
    gpio_init(PIN_IN4);
    gpio_set_dir(PIN_IN4, false);

    gpio_init(PIN_OUT);
    gpio_set_dir(PIN_OUT, true);

    gpio_set_irq_enabled_with_callback(PIN_CLK, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    multicore_launch_core1(mock);

    // Wait forever
    while (1);
}
