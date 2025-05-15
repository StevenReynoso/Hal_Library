
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

ENTRY(Reset_Handler)

SECTIONS
{
    /* Vector table must be first */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* Code and constants */
    .text :
    {
        *(.text*)
        *(.rodata*)
        _etext = .;    /* Needed to copy .data from flash */
    } > FLASH

    /* Initialized data */
    .data : AT(_etext)
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > SRAM

    /* Zero-init section */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
}
