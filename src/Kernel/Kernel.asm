section .text
        global    _start
        extern    init_cpp
        extern    kernel_main

_start:
        call      init_cpp
        call      kernel_main