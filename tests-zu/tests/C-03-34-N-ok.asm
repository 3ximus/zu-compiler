;~~~~~~~~~~  |--variable_node
segment	.data
align	4
_L1:
;~~~~~~~~~~  |  |--string_node
segment	.rodata
align	4
_L2:
	db	"ola", 0
segment	.data
	dd	_L2
;~~~~~~~~~~  |--function_body_node
segment	.text
global	_main:function
align	4
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
;~~~~~~~~~~  |  |--block_node
;~~~~~~~~~~  |  |  |  |--print_node
;~~~~~~~~~~  |  |  |  |--id_node
	push	dword $_L1
	pop	eax
	push	dword [eax]
	call	prints
	add	esp, 4
_L3:
	push	dword [ebp-4]
	pop	eax
	leave
	ret
extern	readi
extern	readd
extern	printi
extern	printd
extern	prints
extern	println
