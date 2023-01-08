	.text
	.global main
main:
	call	readi32 // read number in eax cin >> eax
	movl	%eax, %ebx
	call	readi32
	addl	%ebx, %eax // eax += ebx
	call	writei32 // write number from eax

	call	finish