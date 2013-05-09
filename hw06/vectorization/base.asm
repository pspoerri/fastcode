	.file	"base.c"
	.text
	.p2align 4,,15
	.globl	FIR
	.type	FIR, @function
FIR:
.LFB0:
	.cfi_startproc
	subl	$3, %edx
	testl	%edx, %edx
	jle	.L1
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	vmulss	(%rsi,%rax,4), %xmm3, %xmm5
	vmulss	4(%rsi,%rax,4), %xmm2, %xmm4
	vaddss	%xmm4, %xmm5, %xmm4
	vmulss	8(%rsi,%rax,4), %xmm1, %xmm5
	vaddss	%xmm5, %xmm4, %xmm4
	vmulss	12(%rsi,%rax,4), %xmm0, %xmm5
	vaddss	%xmm5, %xmm4, %xmm4
	vmovss	%xmm4, (%rdi,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %edx
	jg	.L3
.L1:
	rep
	ret
	.cfi_endproc
.LFE0:
	.size	FIR, .-FIR
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
