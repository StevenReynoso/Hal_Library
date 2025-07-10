/**
 * @section example_gpio_blink Basic Example: Blinking LED using GPIO only
 *
 * This example toggles PA5 (LD2 on Nucleo board) in a blocking loop.
 * It does not use any timers — just raw GPIO toggling with delay loops.
 *
 * GPIO Settings:
 * - PA5 configured as output
 *
 * Clock:
 * - AHB1 clock for GPIOA must be enabled
 *
 * @code
 * int main(void) {
 *     gpio_config_t led_cfg = {
 *         .pin = PIN('A', 5),
 *         .mode = GPIO_MODE_OUTPUT,
 *         .otype = GPIO_OTYPE_PUSHPULL,
 *         .speed = GPIO_SPEED_LOW,
 *         .pull = GPIO_NO_PULL
 *     };
 *
 *     rcc_enable_gpio(GET_PORT(led_cfg.pin));
 *     gpio_init(led_cfg);
 *
 *     while (1) {
 *         gpio_write(led_cfg.pin, 1);   // LED ON
 *         for (volatile int i = 0; i < 100000; i++); // crude delay
 *
 *         gpio_write(led_cfg.pin, 0);   // LED OFF
 *         for (volatile int i = 0; i < 100000; i++);
 *     }
 * }
 * @endcode
 */
