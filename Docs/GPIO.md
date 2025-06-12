# GPIO (General Purpose Input Output)

## Key Functions
### void gpio_init(gpio_config_t cfg);
- Works by the use of a struct that allows the user to set which functions they need for their following port, allowing the easy customization for whichever port the user requires,
- Example of Config Type to enter into gpio_init
```
gpio_config_t cfg = {
  .pin = PIN('A', 5),
  .mode = GPIO_MODE_OUTPUT,
  .otype = GPIO_OTYPE_PUSHPULL,
  .speed = GPIO_SPEED_FAST,
  .pull = GPIO_NO_PULL,
 };
```
  
- Selections for MODES, Output Type, Speed, and Pull: 
- ![image](https://github.com/user-attachments/assets/4c6403cc-9dff-4651-8f9c-6d64e075575f)


this allows the user to setup pin, the mode, the output type, the speed register, and the pull up or down resistor, with ease of use into their main function.

### void gpio_write(uint16_t pin, uint8_t value);
- works by writing to an output pin using BSRR (bit set/reset register) to write the pin HIGH or LOW.
- can be used for toggling pins, flashing LED's.

### void gpio_read(uint16_t gpio_pin);
- reads the input pin, by checking the status of the IDR (Input Data Register) for the given pin by the user.
- works well for reading button states, sensors.

### void gpio_set_af(uint16_t pin, uint8_t af);
- sets the alternate function for the pin the user needs set, by writing to AFRL or AFRH (Alternate Function Low or High Register).
![image](https://github.com/user-attachments/assets/78706b16-b522-440e-9c91-9bbdb9869417)
![image](https://github.com/user-attachments/assets/eba27b87-a6f1-4bf2-83e0-6d168ef83473)
- To select which alternate function you are looking for, the documentation from the reference manual talks about the AFRL or AFRH, but that documentation does not state what AF1 - AF15 we should select for our pin,
- so we need to look at the datasheet which will tell us which pin we are trying to use, and which Alternate function we should use for that pin. 


## Example Code


