	.section .rodata
	.global _input
	.type _input, %object
_input:
	.incbin "input2"
	.size _input, .-_input
	.byte 0
