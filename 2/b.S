	.text
	.global main
main:
	call	readi32
	movl	$0, %ecx

loop_start:
	cmpl 	$1, %eax // eax - 1
	jbe	loop_end

	addl	$1, %ecx
	movl	%eax, %edx
	call	writei32
	movl	%edx, %eax

	testl	$1, %eax
	jbe	divisible_by_two

	// eax % 2 == 1

	movl	%eax, %ebx
	shll	$1, %ebx
	addl	%ebx, %eax
	addl	$1, %eax
	jmp	loop_start

divisible_by_two: // eax % 2 == 0
	shrl	$1, %eax // eax >>= 1
	jmp	loop_start

loop_end:
	movl	%ecx, %eax
	call	writei32
	call	finish
