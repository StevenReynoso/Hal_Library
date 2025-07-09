/* 
 * Linker script for STM32F411RE (Cortex-M4)
 * -----------------------------------------
 * Maps FLASH and SRAM memory regions for code, data, and stack.
 * Handles vector table, text (code), data (RW vars), and BSS (zero-initialized).
 */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K  /* On-chip Flash memory */
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K  /* On-chip SRAM */
}

/* Initial stack pointer location (top of SRAM) */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/* Entry point after reset (must match startup code label) */
ENTRY(Reset_Handler)

SECTIONS
{
    /* 
     * Interrupt vector table — must be first in Flash.
     * Contains initial SP value and exception/IRQ handlers.
     */
    .isr_vector :
    {
        KEEP(*(.isr_vector))  /* Startup file defines this section */
    } > FLASH

    /*
     * Program code and read-only data (.text, .rodata).
     * Loaded into Flash and executed from there.
     */
    .text :
    {
        *(.text*)             /* All executable code */
        *(.rodata*)           /* Read-only constants */
        _etext = .;           /* End of text section, start of init data copy */
    } > FLASH

    /*
     * Initialized global/static variables.
     * Stored in Flash but copied to SRAM on boot.
     */
    .data : AT(_etext)
    {
        _sdata = .;           /* Start of data section in RAM */
        *(.data*)             /* RW globals */
        _edata = .;           /* End of data section */
    } > SRAM

    /*
     * Zero-initialized globals/static vars.
     * Cleared to 0 in startup code (not stored in Flash).
     */
    .bss :
    {
        _sbss = .;            /* Start of BSS */
        *(.bss*)              /* Zeroed globals */
        *(COMMON)             /* Uninitialized common symbols */
        _ebss = .;            /* End of BSS */
    } > SRAM
}
