	.text
	.global main
main:
	movl	$228, %eax // eax = 228
	addl	$42, %eax
	movl	$7, %ebx
	subl	%ebx, %eax // eax -= ebx
	incl	%eax // eax++
	decl	%eax // eax--
	//negl	%eax // eax = -eax
	shrl	$1, %ebx // ebx <<= 1
	addl	%ebx, %eax
	mull 	%ebx // (eax, edx) = eax * ebx eax, edx
	imull	%ebx 
	call	writei32
	call finish
