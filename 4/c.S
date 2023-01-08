	.text
	.global calc_stack
calc_stack:
	pushl %ebp
	movl %esp, %ebp

	pushl %esi
	pushl %edi

	xorl %eax, %eax
	movl %ebp, %edx

loop:
	movl 4(%edx), %esi
	movl %esi, %edi

	subl $rec, %esi
	subl $main, %edi

	testl %edi, %edi
	js move_back_rec

	testl %esi, %esi
	js end_loop

	cmpl %edi, %esi
	jg end_loop

move_back_rec:
	incl %eax
	movl (%edx), %edx
	jmp loop

end_loop:
	popl %edi
	popl %esi
	popl %ebx
	ret
