	.global inc_a, A
	.data
A: 	.int 4
	
	.text
inc_a:
	// use eax, ecx, edx
	pushl	%ebx

	movl	A, %ebx
	incl	%ebx
	movl	%ebx, A

	popl	%ebx
	ret