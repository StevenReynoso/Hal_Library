# STM32F4 HAL Library (Bare-Metal)

This project is a custom Hardware Abstraction Layer (HAL) for the STM32F4 microcontroller series, specifically designed for the STM32F446RE. It provides direct, register-level control without relying on the STM32 HAL or CMSIS libraries. Built for learning purposes and to show what is going on underneath the hood.

---

## Features

* **GPIO** – Configure, read, write, and set alternate functions.
* **RCC** – Enable peripheral clocks manually.
* **SPI** – Master mode, full-duplex SPI support.
* **Systick** – Microsecond and millisecond delay functionality.
* **TIM** – Timer initialization and basic configuration.
* **UART** – Transmit, receive, and configure UART communication.

---

## File Structure

```
Hal_Library/
├── core/                  # Contains main.c
├── src/                   # All peripheral source files (hal_gpio.c, etc.)
├── include/               # Public headers (hal_gpio.h, etc.)
│   └── registers/         # Peripheral register mappings (stm32f4_gpio.h, etc.)
├── platform/stm32f4/      # Contains Startup file and linker script
├── build/                 # Build artifacts (generated)
├── Makefile               # Build system
└── README.md              # This file
```

---

## Getting Started

### Dependencies

* `arm-none-eabi-gcc`
* `stlink-tools` (provides `st-flash` and `st-util` for ST-Link programming/debugging)


Install with:

```bash
sudo apt install gcc-arm-none-eabi stlink-tools
```

---

## Build Commands

| Command      | Description                                 |
| ------------ | ------------------------------------------- |
| `make`       | Compiles all source files and links the ELF |
| `make clean` | Removes the `build/` directory              |
| `make flash` | Flashes the `.bin` to STM32 via ST-Link     |
| `make debug` | Launches `st-util` and opens GDB            |

---

## Flashing Notes

* Ensure the STM32 is connected via ST-Link and powered on.
* Flashing uses `st-flash`. The address `0x08000000` is the flash start.
* You may need `sudo` depending on udev rules:

```bash
sudo make flash
```

---

## Debugging Guide

1. Connect your board via USB ST-Link.
2. Start `st-util` manually.
3. Launch GDB (use `gdb-multiarch` if needed):

```bash
gdb-multiarch build/main.elf
```

4. In GDB:

```
(gdb) target extended-remote :4242
(gdb) monitor reset halt
(gdb) continue
```

Optional GDB commands:

* `step`             (single instruction)
* `break <function>` (set breakpoint)
* info registers     (shows registers)
* x/10i $pc          (disassemble instructions at PC)


---

## Doxygen Documentation

To view the generated documentation in your browser, use the helper script:

```bash
./open_docs.sh
```

If the documentation hasn’t been generated yet, run:

```bash
doxygen Doxyfile
```
* Output HTML goes to `docs/html/index.html` by default.
---

## Common Issues

### "No rule to make target 'startup.s'"

* **Cause:** Wrong path to startup file.
* **Fix:** Update `STARTUP` variable in `Makefile`:

  ```make
  STARTUP = platform/stm32f4/startup.s
  ```

### "undefined reference to `main`"

* **Cause:** The linker can't find your `main()` function.
* **Fix:** Ensure `core/main.c` is included in `SRC_DIR` or explicitly added.

### "cannot open file 'st-flash'"

* **Cause:** ST-Link utilities not installed.
* **Fix:**

  ```bash
  sudo apt install stlink-tools
  ```

---

## Contribution Notes

This HAL was built for educational purposes and kept intentionally minimal. Contributions, testing, and refactors are welcome. This library avoids all vendor dependencies for clarity and control.

---

## License

MIT License – Use and modify freely.
