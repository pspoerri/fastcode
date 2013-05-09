	.file	"warmup.c"
	.text
	.p2align 4,,15
	.globl	warmup
	.type	warmup, @function
warmup:
.LFB0:
	.cfi_startproc
	testl	%edx, %edx
	jle	.L1
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movss	4(%rdi,%rax,8), %xmm2
	movss	(%rdi,%rax,8), %xmm1
	divss	%xmm0, %xmm2
	addss	%xmm1, %xmm1
	addss	%xmm2, %xmm1
	movss	%xmm1, (%rsi,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %edx
	jg	.L3
.L1:
	rep
	ret
	.cfi_endproc
.LFE0:
	.size	warmup, .-warmup
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
