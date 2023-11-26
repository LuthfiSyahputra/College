	.file	"core_test.c"
	.intel_syntax noprefix
	.text
	.globl	__clrline__
	.section .rdata,"dr"
.LC0:
	.ascii "\15\33[K\0"
	.data
	.align 8
__clrline__:
	.quad	.LC0
	.text
	.globl	memreset
	.def	memreset;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset
memreset:
	push	rbp
	.seh_pushreg	rbp
	push	rbx
	.seh_pushreg	rbx
	lea	rbp, [rsp]
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	rax, rcx
	mov	rbx, rax
	movsx	rax, edx
	add	rax, rbx
	jmp	.L2
.L3:
	mov	BYTE PTR [rbx], 0
	add	rbx, 1
.L2:
	cmp	rax, rbx
	jne	.L3
	mov	eax, edx
	pop	rbx
	pop	rbp
	ret
	.seh_endproc
	.globl	memreset_t
	.def	memreset_t;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t
memreset_t:
	push	rbp
	.seh_pushreg	rbp
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	lea	rbp, [rsp]
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	QWORD PTR 32[rbp], rcx
	mov	eax, edx
	movsx	rdx, eax
	mov	rcx, rdx
	and	ecx, 7
	mov	rdx, QWORD PTR 32[rbp]
	lea	rbx, [rcx+rdx]
	mov	rsi, QWORD PTR 32[rbp]
	jmp	.L6
.L7:
	mov	BYTE PTR [rsi], 0
	add	rsi, 1
.L6:
	cmp	rsi, rbx
	jne	.L7
	cdqe
	and	rax, -8
	add	rbx, rax
	mov	rsi, QWORD PTR 32[rbp]
	jmp	.L8
.L9:
	mov	QWORD PTR [rsi], 0
	add	rsi, 8
.L8:
	cmp	rbx, rsi
	jne	.L9
	mov	rax, rbx
	sub	rax, QWORD PTR 32[rbp]
	pop	rbx
	pop	rsi
	pop	rbp
	ret
	.seh_endproc
	.globl	memreset_t2
	.def	memreset_t2;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t2
memreset_t2:
	push	rbp
	.seh_pushreg	rbp
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 40
	.seh_stackalloc	40
	lea	rbp, 32[rsp]
	.seh_setframe	rbp, 32
	.seh_endprologue
	mov	QWORD PTR 32[rbp], rcx
	mov	eax, edx
	mov	rbx, QWORD PTR 32[rbp]
	jmp	.L12
.L13:
	mov	QWORD PTR [rbx], 0
	add	rbx, 8
	sub	eax, 8
.L12:
	mov	edx, eax
	cmp	edx, 7
	ja	.L13
	mov	edx, eax
	mov	rcx, rbx
	call	memreset
	cdqe
	sal	rax, 3
	add	rbx, rax
	mov	rax, rbx
	sub	rax, QWORD PTR 32[rbp]
	add	rsp, 40
	pop	rbx
	pop	rbp
	ret
	.seh_endproc
	.globl	memreset_t3
	.def	memreset_t3;	.scl	2;	.type	32;	.endef
	.seh_proc	memreset_t3
memreset_t3:
	push	rbp
	.seh_pushreg	rbp
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 32
	.seh_stackalloc	32
	lea	rbp, 32[rsp]
	.seh_setframe	rbp, 32
	.seh_endprologue
	mov	QWORD PTR 32[rbp], rcx
	mov	eax, edx
	mov	rbx, QWORD PTR 32[rbp]
	movsx	rdx, eax
	and	rdx, -8
	lea	rsi, [rbx+rdx]
	jmp	.L16
.L17:
	mov	QWORD PTR [rbx], 0
	add	rbx, 8
.L16:
	cmp	rbx, rsi
	jne	.L17
	and	eax, 7
	mov	edx, eax
	mov	rcx, rbx
	call	memreset
	cdqe
	add	rbx, rax
	mov	rax, rbx
	sub	rax, QWORD PTR 32[rbp]
	add	rsp, 32
	pop	rbx
	pop	rsi
	pop	rbp
	ret
	.seh_endproc
	.globl	memcpy_h
	.def	memcpy_h;	.scl	2;	.type	32;	.endef
	.seh_proc	memcpy_h
memcpy_h:
	push	rbp
	.seh_pushreg	rbp
	push	rbx
	.seh_pushreg	rbx
	lea	rbp, [rsp]
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	rax, rcx
	mov	DWORD PTR 40[rbp], r8d
	mov	ecx, DWORD PTR 40[rbp]
	lea	rbx, [rax+rcx]
	jmp	.L20
.L21:
	movzx	ecx, BYTE PTR [rax]
	mov	BYTE PTR [rdx], cl
	add	rax, 1
	add	rdx, 1
.L20:
	cmp	rbx, rax
	jne	.L21
	nop
	nop
	pop	rbx
	pop	rbp
	ret
	.seh_endproc
	.globl	memcmp_h
	.def	memcmp_h;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_h
memcmp_h:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	rax, rcx
	mov	ecx, r8d
	jmp	.L23
.L26:
	movzx	r9d, BYTE PTR [rax]
	movzx	r8d, BYTE PTR [rdx]
	cmp	r9b, r8b
	je	.L24
	mov	eax, 0
	jmp	.L25
.L24:
	add	rax, 1
	add	rdx, 1
	sub	ecx, 1
.L23:
	test	ecx, ecx
	jne	.L26
	mov	eax, 1
.L25:
	pop	rbp
	ret
	.seh_endproc
	.globl	memcmp_hc
	.def	memcmp_hc;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_hc
memcmp_hc:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	rax, rcx
	mov	ecx, r8d
	jmp	.L28
.L33:
	movzx	r9d, BYTE PTR [rax]
	movzx	r8d, BYTE PTR [rdx]
	cmp	r9b, r8b
	je	.L29
	movzx	eax, BYTE PTR [rax]
	movzx	edx, BYTE PTR [rdx]
	cmp	dl, al
	jnb	.L30
	mov	eax, 1
	jmp	.L32
.L30:
	mov	eax, -1
	jmp	.L32
.L29:
	add	rax, 1
	add	rdx, 1
	sub	ecx, 1
.L28:
	test	ecx, ecx
	jne	.L33
	mov	eax, 0
.L32:
	pop	rbp
	ret
	.seh_endproc
	.globl	memcmp_hl
	.def	memcmp_hl;	.scl	2;	.type	32;	.endef
	.seh_proc	memcmp_hl
memcmp_hl:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 16
	.seh_stackalloc	16
	.seh_endprologue
	mov	eax, r8d
	mov	DWORD PTR -4[rbp], eax
	jmp	.L35
.L38:
	movzx	r9d, BYTE PTR [rcx]
	movzx	r8d, BYTE PTR [rdx]
	cmp	r9b, r8b
	jne	.L40
	add	rcx, 1
	add	rdx, 1
	sub	eax, 1
.L35:
	test	eax, eax
	jne	.L38
	jmp	.L37
.L40:
	nop
.L37:
	mov	edx, DWORD PTR -4[rbp]
	sub	edx, eax
	mov	eax, edx
	add	rsp, 16
	pop	rbp
	ret
	.seh_endproc
	.globl	memmov
	.def	memmov;	.scl	2;	.type	32;	.endef
	.seh_proc	memmov
memmov:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	rax, rcx
	mov	ecx, r8d
	jmp	.L42
.L43:
	movzx	r8d, BYTE PTR [rax]
	mov	BYTE PTR [rdx], r8b
	mov	BYTE PTR [rax], 0
	add	rax, 1
	add	rdx, 1
	sub	ecx, 1
.L42:
	test	ecx, ecx
	jne	.L43
	nop
	nop
	pop	rbp
	ret
	.seh_endproc
	.def	fprintf;	.scl	3;	.type	32;	.endef
	.seh_proc	fprintf
fprintf:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	QWORD PTR 24[rbp], rdx
	mov	QWORD PTR 32[rbp], r8
	mov	QWORD PTR 40[rbp], r9
	lea	rax, 32[rbp]
	mov	QWORD PTR -16[rbp], rax
	mov	rcx, QWORD PTR -16[rbp]
	mov	rdx, QWORD PTR 24[rbp]
	mov	rax, QWORD PTR 16[rbp]
	mov	r8, rcx
	mov	rcx, rax
	call	__mingw_vfprintf
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.def	snprintf;	.scl	3;	.type	32;	.endef
	.seh_proc	snprintf
snprintf:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	QWORD PTR 24[rbp], rdx
	mov	QWORD PTR 32[rbp], r8
	mov	QWORD PTR 40[rbp], r9
	lea	rax, 40[rbp]
	mov	QWORD PTR -16[rbp], rax
	mov	r8, QWORD PTR -16[rbp]
	mov	rcx, QWORD PTR 32[rbp]
	mov	rdx, QWORD PTR 24[rbp]
	mov	rax, QWORD PTR 16[rbp]
	mov	r9, r8
	mov	r8, rcx
	mov	rcx, rax
	call	__mingw_vsnprintf
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.globl	debugInfo
	.bss
	.align 32
debugInfo:
	.space 50
	.globl	debugbuf
	.align 32
debugbuf:
	.space 4095
	.section .rdata,"dr"
.LC1:
	.ascii "[INFO] {%s/%s :%d} \0"
.LC2:
	.ascii "[INFO] {%s/%s} \0"
	.text
	.globl	info
	.def	info;	.scl	2;	.type	32;	.endef
	.seh_proc	info
info:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	QWORD PTR 24[rbp], rdx
	mov	DWORD PTR 32[rbp], r8d
	cmp	DWORD PTR 32[rbp], 0
	je	.L49
	mov	rdx, QWORD PTR 16[rbp]
	mov	eax, DWORD PTR 32[rbp]
	mov	DWORD PTR 40[rsp], eax
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC1[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
	jmp	.L50
.L49:
	mov	rdx, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC2[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
.L50:
	lea	rax, debugInfo[rip]
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC3:
	.ascii "[DEBUG] {%s/%s :%d} \0"
.LC4:
	.ascii "[DEBUG] {%s/%s} \0"
	.text
	.globl	debug
	.def	debug;	.scl	2;	.type	32;	.endef
	.seh_proc	debug
debug:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	QWORD PTR 24[rbp], rdx
	mov	DWORD PTR 32[rbp], r8d
	cmp	DWORD PTR 32[rbp], 0
	je	.L53
	mov	rdx, QWORD PTR 16[rbp]
	mov	eax, DWORD PTR 32[rbp]
	mov	DWORD PTR 40[rsp], eax
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC3[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
	jmp	.L54
.L53:
	mov	rdx, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC4[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
.L54:
	lea	rax, debugInfo[rip]
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC5:
	.ascii "[WARNING] {%s/%s :%d} \0"
.LC6:
	.ascii "[WARNING] {%s/%s} \0"
	.text
	.globl	warning
	.def	warning;	.scl	2;	.type	32;	.endef
	.seh_proc	warning
warning:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	QWORD PTR 24[rbp], rdx
	mov	DWORD PTR 32[rbp], r8d
	cmp	DWORD PTR 32[rbp], 0
	je	.L57
	mov	rdx, QWORD PTR 16[rbp]
	mov	eax, DWORD PTR 32[rbp]
	mov	DWORD PTR 40[rsp], eax
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC5[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
	jmp	.L58
.L57:
	mov	rdx, QWORD PTR 16[rbp]
	mov	rax, QWORD PTR 24[rbp]
	mov	QWORD PTR 32[rsp], rax
	mov	r9, rdx
	lea	r8, .LC6[rip]
	mov	edx, 50
	lea	rax, debugInfo[rip]
	mov	rcx, rax
	call	snprintf
.L58:
	lea	rax, debugInfo[rip]
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
.lcomm flog,8,8
	.section .rdata,"dr"
.LC7:
	.ascii "ab\0"
.LC8:
	.ascii "lib/Tools/Debug.h\0"
	.align 8
.LC9:
	.ascii "%s error opening/creating log file \"~\\%s\"\12\0"
	.text
	.globl	flog_init
	.def	flog_init;	.scl	2;	.type	32;	.endef
	.seh_proc	flog_init
flog_init:
	push	rbp
	.seh_pushreg	rbp
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 40
	.seh_stackalloc	40
	lea	rbp, 32[rsp]
	.seh_setframe	rbp, 32
	.seh_endprologue
	mov	QWORD PTR 32[rbp], rcx
	mov	rax, QWORD PTR 32[rbp]
	lea	rdx, .LC7[rip]
	mov	rcx, rax
	call	fopen
	mov	QWORD PTR flog[rip], rax
	mov	rax, QWORD PTR flog[rip]
	test	rax, rax
	jne	.L61
	mov	r8d, 89
	lea	rax, __func__.2[rip]
	mov	rdx, rax
	lea	rax, .LC8[rip]
	mov	rcx, rax
	call	warning
	mov	rbx, rax
	mov	ecx, 2
	mov	rax, QWORD PTR __imp___acrt_iob_func[rip]
	call	rax
	mov	rcx, rax
	mov	rax, QWORD PTR 32[rbp]
	mov	r9, rax
	mov	r8, rbx
	lea	rax, .LC9[rip]
	mov	rdx, rax
	call	fprintf
	mov	eax, 0
	jmp	.L62
.L61:
	mov	rax, QWORD PTR flog[rip]
.L62:
	add	rsp, 40
	pop	rbx
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC10:
	.ascii "%s Error opening / creating log file \"~/%s\"\12\0"
.LC11:
	.ascii "%s\12\0"
	.text
	.globl	debug_log
	.def	debug_log;	.scl	2;	.type	32;	.endef
	.seh_proc	debug_log
debug_log:
	push	rbp
	.seh_pushreg	rbp
	push	rbx
	.seh_pushreg	rbx
	mov	eax, 4152
	call	___chkstk_ms
	sub	rsp, rax
	.seh_stackalloc	4152
	lea	rbp, 128[rsp]
	.seh_setframe	rbp, 128
	.seh_endprologue
	mov	QWORD PTR 4048[rbp], rcx
	mov	QWORD PTR 4056[rbp], rdx
	mov	rax, QWORD PTR 4056[rbp]
	lea	rdx, .LC7[rip]
	mov	rcx, rax
	call	fopen
	mov	QWORD PTR 4008[rbp], rax
	cmp	QWORD PTR 4008[rbp], 0
	jne	.L64
	mov	r8d, 103
	lea	rax, __func__.1[rip]
	mov	rdx, rax
	lea	rax, .LC8[rip]
	mov	rcx, rax
	call	warning
	mov	rbx, rax
	mov	ecx, 2
	mov	rax, QWORD PTR __imp___acrt_iob_func[rip]
	call	rax
	mov	rcx, rax
	mov	rax, QWORD PTR 4056[rbp]
	mov	r9, rax
	mov	r8, rbx
	lea	rax, .LC10[rip]
	mov	rdx, rax
	call	fprintf
	mov	eax, 0
	jmp	.L66
.L64:
	mov	rdx, QWORD PTR 4048[rbp]
	lea	rax, -96[rbp]
	mov	r9, rdx
	lea	r8, .LC11[rip]
	mov	edx, 4095
	mov	rcx, rax
	call	snprintf
	mov	DWORD PTR 4004[rbp], eax
	mov	eax, DWORD PTR 4004[rbp]
	movsx	rdx, eax
	mov	rcx, QWORD PTR 4008[rbp]
	lea	rax, -96[rbp]
	mov	r9, rcx
	mov	r8, rdx
	mov	edx, 1
	mov	rcx, rax
	call	fwrite
	mov	rax, QWORD PTR 4008[rbp]
	mov	rcx, rax
	call	fclose
	mov	eax, 1
.L66:
	add	rsp, 4152
	pop	rbx
	pop	rbp
	ret
	.seh_endproc
	.globl	memfree
	.def	memfree;	.scl	2;	.type	32;	.endef
	.seh_proc	memfree
memfree:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	cmp	QWORD PTR 16[rbp], 0
	je	.L70
	mov	rax, QWORD PTR 16[rbp]
	mov	rcx, rax
	call	free
	mov	QWORD PTR 16[rbp], 0
	jmp	.L67
.L70:
	nop
.L67:
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC12:
	.ascii "lib/mem_ex.h\0"
	.align 8
.LC13:
	.ascii "%s Error Allocating memory [%llu byte%c]\12\0"
	.text
	.globl	memswap_s
	.def	memswap_s;	.scl	2;	.type	32;	.endef
	.seh_proc	memswap_s
memswap_s:
	push	rbp
	.seh_pushreg	rbp
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 48
	.seh_stackalloc	48
	lea	rbp, 48[rsp]
	.seh_setframe	rbp, 48
	.seh_endprologue
	mov	QWORD PTR 32[rbp], rcx
	mov	DWORD PTR 40[rbp], edx
	mov	rax, QWORD PTR 32[rbp]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	je	.L72
	mov	rax, QWORD PTR 32[rbp]
	mov	rax, QWORD PTR [rax]
	mov	rcx, rax
	call	free
	mov	rax, QWORD PTR 32[rbp]
	mov	QWORD PTR [rax], 0
.L72:
	mov	eax, DWORD PTR 40[rbp]
	cdqe
	mov	rcx, rax
	call	malloc
	mov	rdx, rax
	mov	rax, QWORD PTR 32[rbp]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR 32[rbp]
	mov	rax, QWORD PTR [rax]
	test	rax, rax
	jne	.L76
	cmp	DWORD PTR 40[rbp], 1
	jle	.L74
	mov	esi, 115
	jmp	.L75
.L74:
	mov	esi, 0
.L75:
	mov	r8d, 52
	lea	rax, __func__.0[rip]
	mov	rdx, rax
	lea	rax, .LC12[rip]
	mov	rcx, rax
	call	warning
	mov	rbx, rax
	mov	ecx, 2
	mov	rax, QWORD PTR __imp___acrt_iob_func[rip]
	call	rax
	mov	rcx, rax
	mov	eax, DWORD PTR 40[rbp]
	mov	DWORD PTR 32[rsp], esi
	mov	r9d, eax
	mov	r8, rbx
	lea	rax, .LC13[rip]
	mov	rdx, rax
	call	fprintf
.L76:
	nop
	add	rsp, 48
	pop	rbx
	pop	rsi
	pop	rbp
	ret
	.seh_endproc
	.globl	memswap
	.def	memswap;	.scl	2;	.type	32;	.endef
	.seh_proc	memswap
memswap:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	QWORD PTR 16[rbp], rcx
	mov	DWORD PTR 24[rbp], edx
	cmp	QWORD PTR 16[rbp], 0
	je	.L78
	mov	rax, QWORD PTR 16[rbp]
	mov	rcx, rax
	call	free
.L78:
	mov	eax, DWORD PTR 24[rbp]
	cdqe
	mov	rcx, rax
	call	malloc
	add	rsp, 32
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
	sub	rsp, 96
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	mov	QWORD PTR -32[rbp], 1971210
	mov	QWORD PTR -24[rbp], 0
	mov	DWORD PTR -16[rbp], 0
	mov	QWORD PTR -64[rbp], 660490
	mov	QWORD PTR -56[rbp], 0
	mov	DWORD PTR -48[rbp], 0
	lea	rdx, -64[rbp]
	lea	rax, -32[rbp]
	mov	r8d, 3
	mov	rcx, rax
	call	memcmp_h
	add	rsp, 96
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
__func__.2:
	.ascii "flog_init\0"
	.align 8
__func__.1:
	.ascii "debug_log\0"
	.align 8
__func__.0:
	.ascii "memswap_s\0"
	.ident	"GCC: (Rev1, Built by MSYS2 project) 13.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	__mingw_vsnprintf;	.scl	2;	.type	32;	.endef
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	fwrite;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
