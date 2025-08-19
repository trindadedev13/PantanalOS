OUTPUT_FORMAT("binary")
ENTRY(_start)

SECTIONS
{
    /** kernel start addr */
    . = 0x7E00;

    /** kernel code */
    .text :
    {
        *(.text._start)
        *(.text*)
    }

    /** consts */
    .rodata :
    {
        *(.rodata*)
    }

    /** initialized data */
    .data :
    {
        *(.data*)
    }

    /** not initialized data */
    .bss :
    {
        *(.bss*)
        *(COMMON)
    }

    /** cpp global constructors */
    .init_array :
    {
        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        __init_array_end = .;
    }


    __kernel_end = .;
}