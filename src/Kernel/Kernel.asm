section .text
        global    _start
        global    __cxa_pure_virtual
        extern    init_cpp
        extern    kernel_main

_start:
        call      init_cpp
        call      kernel_main

__cxa_pure_virtual:
        jmp       $