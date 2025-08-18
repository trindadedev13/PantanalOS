ENTRY(_start)

SECTIONS
{
    . = 0x7E00; /** kernel starts at 0x7e00 */

    .text : ALIGN(4096)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }

    .init_array : ALIGN(16)
    {
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
    }

    .data : ALIGN(4096)
    {
        *(.data)
    }

    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
    }
}