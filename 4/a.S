	.text
	.global main
main:
	xorl	%esi, %esi

read_loop:
	call 	read_int

	cmpl	$1, %eax
	jne	loop_end

	xorl	a, %esi
	jmp 	read_loop


loop_end:
	movl	%esi, %eax
	call 	write_int
	ret


read_int:
	pushl	%ebp
	movl	%esp, %ebp
	
	pushl	$a
	pushl	$scanf_str
	call	scanf

	movl	%ebp, %esp
	popl	%ebp
	ret


write_int:
	pushl	%ebp
	movl	%esp, %ebp
	
	pushl	%eax
	pushl	$printf_str
	call	printf

	movl	%ebp, %esp
	popl	%ebp
	ret

	.data
a: 	.int 0

	.text
scanf_str:	.asciz "%d"
printf_str:	.asciz "%d\n"