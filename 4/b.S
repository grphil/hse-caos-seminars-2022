	.text
	.global sumab
sumab:
	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %eax
	addl 12(%ebp), %eax

	movl %ebp, %esp
	popl %ebp
	ret