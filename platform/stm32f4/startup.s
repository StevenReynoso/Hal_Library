.syntax unified
.cpu cortex-m4
.thumb

/* -----------------------------------------------------------------------------
 * Interrupt Vector Table
 * -------------------------------------------------------------------------- */
.section .isr_vector, "a", %progbits
.global _vector_table
.type _vector_table, %object
.size _vector_table, . - _vector_table

/* 
 * @brief Interrupt vector table for Cortex-M4
 * The first entry is the initial stack pointer value.
 * The second entry is the address of Reset_Handler().
 * All other entries are exception/IRQ handlers.
 */
_vector_table:
    .word _estack            /* Initial stack pointer (top of SRAM) */
    .word Reset_Handler      /* Reset vector */
    .word NMI
    .word Hard_Fault
    .word Mem_Manage
    .word Bus_Fault
    .word Usage_Fault
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word SVCall
    .word Debug_Monitor
    .word 0                  /* Reserved */
    .word PendSV
    .word SysTick_Handler

/* -----------------------------------------------------------------------------
 * Reset Handler
 * -------------------------------------------------------------------------- */
.section .text
.global Reset_Handler
.type Reset_Handler, %function

/**
 * @brief Reset_Handler - Entry point after MCU reset.
 *
 * - Copies initialized data from FLASH (.data) to SRAM
 * - Clears uninitialized data (.bss)
 * - Calls main()
 */
Reset_Handler:
    ldr r0, =_sdata          /* Start of .data in SRAM */
    ldr r1, =_etext          /* End of .text in FLASH (start of init data) */
    ldr r2, =_edata          /* End of .data in SRAM */

.data_copy:
    cmp r0, r2
    ittt lt                  /* If r0 < r2, copy word from r1 to r0 */
    ldrlt r3, [r1], #4
    strlt r3, [r0], #4
    blt .data_copy

    ldr r0, =_sbss           /* Start of .bss */
    ldr r1, =_ebss           /* End of .bss */
    movs r2, #0              /* Zero value for clearing */

.bss_clear:
    cmp r0, r1
    it lt
    strlt r2, [r0], #4
    blt .bss_clear

    bl main                  /* Jump to main() */

/* Infinite loop fallback */
infinite_loop:
    b infinite_loop

/* -----------------------------------------------------------------------------
 * Weak default handlers (fallback to infinite loop)
 * -------------------------------------------------------------------------- */
.weak NMI, Hard_Fault, Mem_Manage, Bus_Fault, Usage_Fault, SVCall, Debug_Monitor, PendSV, SysTick_Handler
.thumb_set NMI,            infinite_loop
.thumb_set Hard_Fault,     infinite_loop
.thumb_set Mem_Manage,     infinite_loop
.thumb_set Bus_Fault,      infinite_loop
.thumb_set Usage_Fault,    infinite_loop
.thumb_set SVCall,         infinite_loop
.thumb_set Debug_Monitor,  infinite_loop
.thumb_set PendSV,         infinite_loop
.thumb_set SysTick_Handler,infinite_loop
