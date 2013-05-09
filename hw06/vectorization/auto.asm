	.file	"auto.c"
	.text
	.p2align 4,,15
	.globl	FIR
	.type	FIR, @function
FIR:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	subl	$3, %edx
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	addq	$16, %rsp
	testl	%edx, %edx
	jle	.L1
	leaq	32(%rdi), %r9
	movl	%edx, %r8d
	shrl	$3, %r8d
	leal	0(,%r8,8), %r11d
	testl	%r11d, %r11d
	je	.L6
	leaq	32(%rsi), %rax
	cmpl	$7, %edx
	seta	%cl
	cmpq	%rax, %rdi
	seta	%r10b
	cmpq	%r9, %rsi
	seta	%al
	orl	%eax, %r10d
	leaq	36(%rsi), %rax
	andl	%r10d, %ecx
	cmpq	%rax, %rdi
	leaq	4(%rsi), %rax
	seta	%r10b
	cmpq	%rax, %r9
	setb	%al
	orl	%eax, %r10d
	leaq	40(%rsi), %rax
	andl	%r10d, %ecx
	cmpq	%rax, %rdi
	leaq	8(%rsi), %rax
	seta	%r10b
	cmpq	%rax, %r9
	setb	%al
	orl	%eax, %r10d
	leaq	44(%rsi), %rax
	andl	%r10d, %ecx
	cmpq	%rax, %rdi
	leaq	12(%rsi), %rax
	seta	%r10b
	cmpq	%rax, %r9
	setb	%al
	orl	%eax, %r10d
	testb	%r10b, %cl
	je	.L6
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	vshufps	$0, %xmm3, %xmm3, %xmm9
	vshufps	$0, %xmm2, %xmm2, %xmm8
	vshufps	$0, %xmm1, %xmm1, %xmm7
	vshufps	$0, %xmm0, %xmm0, %xmm6
	vinsertf128	$1, %xmm9, %ymm9, %ymm9
	vinsertf128	$1, %xmm8, %ymm8, %ymm8
	vinsertf128	$1, %xmm7, %ymm7, %ymm7
	vinsertf128	$1, %xmm6, %ymm6, %ymm6
	.p2align 4,,10
	.p2align 3
.L4:
	vmovups	(%rsi,%rax), %xmm5
	addl	$1, %ecx
	vmovups	4(%rsi,%rax), %xmm4
	vinsertf128	$0x1, 16(%rsi,%rax), %ymm5, %ymm5
	vmulps	%ymm9, %ymm5, %ymm5
	vinsertf128	$0x1, 20(%rsi,%rax), %ymm4, %ymm4
	vmulps	%ymm8, %ymm4, %ymm4
	vaddps	%ymm4, %ymm5, %ymm4
	vmovups	8(%rsi,%rax), %xmm5
	vinsertf128	$0x1, 24(%rsi,%rax), %ymm5, %ymm5
	vmulps	%ymm7, %ymm5, %ymm5
	vaddps	%ymm5, %ymm4, %ymm4
	vmovups	12(%rsi,%rax), %xmm5
	vinsertf128	$0x1, 28(%rsi,%rax), %ymm5, %ymm5
	vmulps	%ymm6, %ymm5, %ymm5
	vaddps	%ymm5, %ymm4, %ymm4
	vmovups	%xmm4, (%rdi,%rax)
	vextractf128	$0x1, %ymm4, 16(%rdi,%rax)
	addq	$32, %rax
	cmpl	%ecx, %r8d
	ja	.L4
	cmpl	%r11d, %edx
	movl	%r11d, %eax
	je	.L1
.L3:
	movslq	%eax, %rcx
	salq	$2, %rcx
	addq	%rcx, %rsi
	addq	%rcx, %rdi
	.p2align 4,,10
	.p2align 3
.L5:
	vmulss	(%rsi), %xmm3, %xmm5
	addl	$1, %eax
	vmulss	4(%rsi), %xmm2, %xmm4
	vaddss	%xmm4, %xmm5, %xmm4
	vmulss	8(%rsi), %xmm1, %xmm5
	vaddss	%xmm5, %xmm4, %xmm4
	vmulss	12(%rsi), %xmm0, %xmm5
	addq	$4, %rsi
	vaddss	%xmm5, %xmm4, %xmm4
	vmovss	%xmm4, (%rdi)
	addq	$4, %rdi
	cmpl	%eax, %edx
	jg	.L5
.L1:
	leave
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	vzeroupper
	ret
.L6:
	.cfi_restore_state
	xorl	%eax, %eax
	jmp	.L3
	.cfi_endproc
.LFE0:
	.size	FIR, .-FIR
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
