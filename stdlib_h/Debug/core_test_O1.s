	.file	"core_test.c"
	.intel_syntax noprefix
	.text
	.globl	memreset
	.def	memreset;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset
memreset:
	.seh_endprologue
	mov	eax, edx
	movsx	r8, edx
	add	r8, rcx
	cmp	rcx, r8
	je	.L2
.L3:
	mov	BYTE PTR [rcx], 0
	add	rcx, 1
	cmp	r8, rcx
	jne	.L3
.L2:
	ret
	.seh_endproc
	.globl	memreset_t
	.def	memreset_t;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t
memreset_t:
	.seh_endprologue
	mov	eax, edx
	and	eax, 7
	add	rax, rcx
	cmp	rcx, rax
	je	.L6
	mov	r8, rcx
.L7:
	mov	BYTE PTR [r8], 0
	add	r8, 1
	cmp	rax, r8
	jne	.L7
.L6:
	movsx	rdx, edx
	and	rdx, -8
	add	rax, rdx
	cmp	rcx, rax
	je	.L8
	mov	rdx, rcx
.L9:
	mov	QWORD PTR [rdx], 0
	add	rdx, 8
	cmp	rax, rdx
	jne	.L9
.L8:
	sub	eax, ecx
	ret
	.seh_endproc
	.globl	memreset_t2
	.def	memreset_t2;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t2
memreset_t2:
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	mov	rsi, rcx
	cmp	edx, 7
	jbe	.L15
	sub	edx, 8
	mov	ecx, edx
	shr	ecx, 3
	lea	eax, 1[rcx]
	mov	eax, eax
	lea	rbx, [rsi+rax*8]
	mov	rax, rsi
.L14:
	mov	QWORD PTR [rax], 0
	add	rax, 8
	cmp	rax, rbx
	jne	.L14
	sal	ecx, 3
	sub	edx, ecx
.L13:
	mov	rcx, rbx
	call	memreset
	lea	eax, [rbx+rax*8]
	sub	eax, esi
	add	rsp, 40
	pop	rbx
	pop	rsi
	ret
.L15:
	mov	rbx, rcx
	jmp	.L13
	.seh_endproc
	.globl	memreset_t3
	.def	memreset_t3;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t3
memreset_t3:
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	mov	rsi, rcx
	movsx	rbx, edx
	and	rbx, -8
	add	rbx, rcx
	cmp	rcx, rbx
	je	.L18
	mov	rax, rcx
.L19:
	mov	QWORD PTR [rax], 0
	add	rax, 8
	cmp	rbx, rax
	jne	.L19
.L18:
	and	edx, 7
	mov	rcx, rbx
	call	memreset
	lea	eax, [rax+rbx]
	sub	eax, esi
	add	rsp, 40
	pop	rbx
	pop	rsi
	ret
	.seh_endproc
	.globl	memcpy_h
	.def	memcpy_h;	.scl	2;	.type	32;	.endef
	.seh_proc	memcpy_h
memcpy_h:
	.seh_endprologue
	mov	r8d, r8d
	lea	rax, [rcx+r8]
	cmp	rcx, rax
	je	.L21
	mov	eax, 0
.L23:
	movzx	r9d, BYTE PTR [rcx+rax]
	mov	BYTE PTR [rdx+rax], r9b
	add	rax, 1
	cmp	r8, rax
	jne	.L23
.L21:
	ret
	.seh_endproc
	.globl	memcmp_h
	.def	memcmp_h;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_h
memcmp_h:
	.seh_endprologue
	test	r8d, r8d
	je	.L28
	mov	r8d, r8d
	mov	eax, 0
.L27:
	movzx	r9d, BYTE PTR [rdx+rax]
	cmp	BYTE PTR [rcx+rax], r9b
	jne	.L29
	add	rax, 1
	cmp	rax, r8
	jne	.L27
	mov	eax, 1
	jmp	.L25
.L28:
	mov	eax, 1
	jmp	.L25
.L29:
	mov	eax, 0
.L25:
	ret
	.seh_endproc
	.globl	memcmp_hc
	.def	memcmp_hc;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_hc
memcmp_hc:
	.seh_endprologue
	test	r8d, r8d
	je	.L35
	mov	r8d, r8d
	mov	eax, 0
.L34:
	movzx	r9d, BYTE PTR [rcx+rax]
	movzx	r10d, BYTE PTR [rdx+rax]
	cmp	r9b, r10b
	jne	.L38
	add	rax, 1
	cmp	rax, r8
	jne	.L34
	mov	eax, 0
	jmp	.L31
.L38:
	cmp	r10b, r9b
	sbb	eax, eax
	and	eax, 2
	sub	eax, 1
.L31:
	ret
.L35:
	mov	eax, 0
	jmp	.L31
	.seh_endproc
	.globl	memcmp_hl
	.def	memcmp_hl;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_hl
memcmp_hl:
	.seh_endprologue
	test	r8d, r8d
	je	.L43
	mov	r10d, r8d
	mov	r9d, 0
.L42:
	movzx	eax, BYTE PTR [rdx+r9]
	cmp	BYTE PTR [rcx+r9], al
	jne	.L45
	add	r9, 1
	cmp	r9, r10
	jne	.L42
	mov	edx, 0
	jmp	.L40
.L45:
	mov	edx, r8d
	sub	edx, r9d
.L40:
	mov	eax, r8d
	sub	eax, edx
	ret
.L43:
	mov	edx, r8d
	jmp	.L40
	.seh_endproc
	.globl	memmov
	.def	memmov;	.scl	2;	.type	32;	.endef
	.seh_proc	memmov
memmov:
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	mov	rbx, rcx
	mov	esi, r8d
	call	memcpy_h
	mov	edx, esi
	mov	rcx, rbx
	call	memreset
	nop
	add	rsp, 40
	pop	rbx
	pop	rsi
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	sub	rsp, 104
	.seh_stackalloc	104
	.seh_endprologue
	call	__main
	mov	QWORD PTR 64[rsp], 1971210
	mov	QWORD PTR 72[rsp], 0
	mov	DWORD PTR 80[rsp], 0
	mov	QWORD PTR 32[rsp], 660490
	mov	QWORD PTR 40[rsp], 0
	mov	DWORD PTR 48[rsp], 0
	lea	rdx, 32[rsp]
	lea	rcx, 64[rsp]
	mov	r8d, 3
	call	memcmp_h
	add	rsp, 104
	ret
	.seh_endproc
	.globl	__clrline__
	.section .rdata,"dr"
.LC0:
	.ascii "\15\33[K\0"
	.data
	.align 8
__clrline__:
	.quad	.LC0
	.ident	"GCC: (Rev1, Built by MSYS2 project) 13.2.0"
