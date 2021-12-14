 .section .rodata
 .global _input
 .type _input, %object
 .align 4
_input:
 .incbin "input"
_input_end:
 .byte 0
