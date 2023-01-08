	.text
	.global main
main:
	call readi32
	pushl %eax
	call recurse
	call finish

recurse: // recurse(a) {if (a == 0) return else {recurse(a - 1), printf(a)}}
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	testl	%eax, %eax
	jz	end_recurse
	subl	$1, %eax
	pushl	%eax 
	call	recurse
	movl	8(%ebp), %eax
	call	writei32
end_recurse:
	movl	%ebp, %esp
	popl 	%ebp
	ret


write1:
	pushl %eax
	movl $228, %eax
	call writei32
	popl %eax
	ret
