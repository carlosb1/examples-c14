	.file	"pure_functions.cpp"
	.text
	.p2align 4,,15
	.globl	_Z6squarei
	.type	_Z6squarei, @function
_Z6squarei:
.LFB0:
	.cfi_startproc
	imull	%edi, %edi
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_Z6squarei, .-_Z6squarei
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	imull	%edi, %edi
	leal	(%rdi,%rdi), %eax
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-21ubuntu1~16.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
