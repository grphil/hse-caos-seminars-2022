	.text
	.global main
main:
	call	readi32
	movl	%eax, %ebx // ebx stores size
	movl	%esp, %ecx // ecx stores initial stack
	
read_seq: // read sequence and check it
	testl	%ebx, %ebx
	jz	finish_read
	decl	%ebx // ebx--

	call	readi32 // eax stores next number
	cmpl	$0, %eax
	jl	negative

	pushl	%eax
	jmp	read_seq

negative:
	cmpl	%esp, %ecx
	je	wrong_sequence
	popl	%edx
	addl	%eax, %edx
	jnz	wrong_sequence
	jmp	read_seq

finish_read:
	cmpl	%esp, %ecx
	jne	wrong_sequence

	movl	$1, %eax
	call	writei32
	call 	finish

wrong_sequence:
	movl	$0, %eax
	call 	writei32
	call	finish

