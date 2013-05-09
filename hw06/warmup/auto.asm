	.file	"auto.c"
	.text
	.p2align 4,,15
	.globl	warmup
	.type	warmup, @function
warmup:
.LFB0:
	.cfi_startproc
	testl	%edx, %edx
	jle	.L1
	movl	%edx, %r9d
	movl	%edx, %ecx
	shrl	$2, %r9d
	leal	0(,%r9,4), %r8d
	testl	%r8d, %r8d
	je	.L6
	leaq	(%rdi,%rcx,8), %rax
	cmpl	$5, %edx
	leaq	(%rsi,%rcx,4), %rcx
	seta	%r10b
	cmpq	%rax, %rsi
	seta	%al
	cmpq	%rcx, %rdi
	seta	%cl
	orl	%ecx, %eax
	testb	%al, %r10b
	je	.L6
	movaps	%xmm0, %xmm1
	movaps	.LC0(%rip), %xmm4
	xorl	%eax, %eax
	shufps	$0, %xmm1, %xmm1
	xorl	%ecx, %ecx
	movaps	%xmm1, %xmm5
	.p2align 4,,10
	.p2align 3
.L4:
	movups	(%rdi,%rax,2), %xmm2
	addl	$1, %ecx
	movups	16(%rdi,%rax,2), %xmm3
	movaps	%xmm2, %xmm1
	shufps	$221, %xmm3, %xmm2
	divps	%xmm5, %xmm2
	shufps	$136, %xmm3, %xmm1
	mulps	%xmm4, %xmm1
	addps	%xmm2, %xmm1
	movups	%xmm1, (%rsi,%rax)
	addq	$16, %rax
	cmpl	%ecx, %r9d
	ja	.L4
	cmpl	%r8d, %edx
	je	.L10
.L3:
	leal	(%r8,%r8), %ecx
	movslq	%r8d, %r9
	xorl	%eax, %eax
	movslq	%ecx, %rcx
	leaq	(%rdi,%rcx,4), %rcx
	leaq	(%rsi,%r9,4), %rdi
	.p2align 4,,10
	.p2align 3
.L5:
	movss	4(%rcx,%rax,8), %xmm2
	movss	(%rcx,%rax,8), %xmm1
	divss	%xmm0, %xmm2
	addss	%xmm1, %xmm1
	addss	%xmm2, %xmm1
	movss	%xmm1, (%rdi,%rax,4)
	addq	$1, %rax
	leal	(%r8,%rax), %esi
	cmpl	%esi, %edx
	jg	.L5
.L1:
	rep
	ret
.L6:
	xorl	%r8d, %r8d
	jmp	.L3
.L10:
	.p2align 4,,8
	ret
	.cfi_endproc
.LFE0:
	.size	warmup, .-warmup
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
