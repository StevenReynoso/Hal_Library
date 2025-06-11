# GPIO (General Purpose Input Output)

# Key Functions
void gpio_init(gpio_config_t cfg);
- Works by the use of a struct that allows the user to set which functions they need for their following port, allowing the easy customization for whichever port the user requires,
example gpio_config_t cfg = {
  .pin = PIN('A', 5),
  .mode = GPIO_MODE_OUTPUT,
  .otype = GPIO_OTYPE_PUSHPULL,
  .speed = GPIO_SPEED_FAST,
  .pull = GPIO_NO_PULL,
};

this allows the user to setup pin, the mode, the output type, the speed register, and the pull up or down resistor.

void gpio_write(uint16_t pin, uint8_t value);
- works by writing to an output pin using BSRR (bit set/reset register) to write the pin HIGH or LOW.
- can be used for toggling pins, flashing LED's.

void gpio_read(uint16_t gpio_pin);
- reads the input pin, by checking the status of the IDR (Input Data Register) for the given pin by the user.
- works well for reading button states, sensors.

void gpio_set_af(uint16_t pin, uint8_t af);
- sets the alternate function for the pin the user needs set, by writing to AFRL or AFRH (Alternate Function Low or High Register).
- 
