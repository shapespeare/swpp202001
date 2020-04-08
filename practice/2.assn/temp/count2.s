	.text
	.file	"count2.ll"
	.globl	count_even              # -- Begin function count_even
	.p2align	4, 0x90
	.type	count_even,@function
count_even:                             # @count_even
	.cfi_startproc
# %bb.0:                                # %entry
	testl	%esi, %esi
	jle	.LBB0_1
# %bb.3:                                # %for.body.preheader
	movl	%esi, %ecx
	xorl	%eax, %eax
	.p2align	4, 0x90
.LBB0_4:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rdi), %edx
	notl	%edx
	andl	$1, %edx
	addl	%edx, %eax
	addq	$4, %rdi
	decq	%rcx
	jne	.LBB0_4
# %bb.2:                                # %for.cond.cleanup
	retq
.LBB0_1:
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	count_even, .Lfunc_end0-count_even
	.cfi_endproc
                                        # -- End function

	.section	".note.GNU-stack","",@progbits
