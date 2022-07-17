	.section .rodata
	.global _input
	.type _input, %object
_input:
	.incbin "input"
	.size _input, .-_input
	.byte 0
