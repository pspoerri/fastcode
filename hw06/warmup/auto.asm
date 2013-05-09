	.file	"auto.c"
	.text
	.p2align 4,,15
	.globl	warmup
	.type	warmup, @function
warmup:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	addq	$16, %rsp
	testl	%edx, %edx
	jle	.L1
	movl	%edx, %r9d
	movl	%edx, %ecx
	shrl	$3, %r9d
	leal	0(,%r9,8), %r8d
	testl	%r8d, %r8d
	je	.L6
	leaq	(%rdi,%rcx,8), %rax
	cmpl	$7, %edx
	leaq	(%rsi,%rcx,4), %rcx
	seta	%r10b
	cmpq	%rax, %rsi
	seta	%al
	cmpq	%rcx, %rdi
	seta	%cl
	orl	%ecx, %eax
	testb	%al, %r10b
	je	.L6
	vmovaps	.LC0(%rip), %ymm6
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	vshufps	$0, %xmm0, %xmm0, %xmm7
	vinsertf128	$1, %xmm7, %ymm7, %ymm7
	.p2align 4,,10
	.p2align 3
.L4:
	vmovups	(%rdi,%rax,2), %xmm4
	addl	$1, %ecx
	vmovups	32(%rdi,%rax,2), %xmm2
	vinsertf128	$0x1, 16(%rdi,%rax,2), %ymm4, %ymm4
	vinsertf128	$0x1, 48(%rdi,%rax,2), %ymm2, %ymm2
	vshufps	$136, %ymm2, %ymm4, %ymm3
	vshufps	$221, %ymm2, %ymm4, %ymm2
	vperm2f128	$3, %ymm3, %ymm3, %ymm1
	vshufps	$68, %ymm1, %ymm3, %ymm5
	vshufps	$238, %ymm1, %ymm3, %ymm1
	vperm2f128	$32, %ymm1, %ymm5, %ymm1
	vmulps	%ymm6, %ymm1, %ymm3
	vperm2f128	$3, %ymm2, %ymm2, %ymm1
	vshufps	$68, %ymm1, %ymm2, %ymm4
	vshufps	$238, %ymm1, %ymm2, %ymm1
	vperm2f128	$32, %ymm1, %ymm4, %ymm1
	vdivps	%ymm7, %ymm1, %ymm1
	vaddps	%ymm1, %ymm3, %ymm1
	vmovups	%xmm1, (%rsi,%rax)
	vextractf128	$0x1, %ymm1, 16(%rsi,%rax)
	addq	$32, %rax
	cmpl	%ecx, %r9d
	ja	.L4
	cmpl	%r8d, %edx
	je	.L1
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
	vmovss	4(%rcx,%rax,8), %xmm2
	vmovss	(%rcx,%rax,8), %xmm1
	vdivss	%xmm0, %xmm2, %xmm2
	vaddss	%xmm1, %xmm1, %xmm1
	vaddss	%xmm2, %xmm1, %xmm1
	vmovss	%xmm1, (%rdi,%rax,4)
	addq	$1, %rax
	leal	(%r8,%rax), %esi
	cmpl	%esi, %edx
	jg	.L5
.L1:
	leave
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	vzeroupper
	ret
.L6:
	.cfi_restore_state
	xorl	%r8d, %r8d
	jmp	.L3
	.cfi_endproc
.LFE0:
	.size	warmup, .-warmup
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
.LC0:
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.long	1073741824
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
