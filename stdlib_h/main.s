	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	func
	.def	func;	.scl	2;	.type	32;	.endef
	.seh_proc	func
func:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	nop
	pop	rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	mov	BYTE PTR -8[rbp], 0
	mov	BYTE PTR -7[rbp], 1
	mov	BYTE PTR -6[rbp], 1
	mov	BYTE PTR -5[rbp], -1
	lea	rax, -8[rbp]
	mov	eax, DWORD PTR [rax]
	or	eax, -16777216
	mov	DWORD PTR -4[rbp], eax
	nop
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev10, Built by MSYS2 project) 12.2.0"
