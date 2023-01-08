	.bss
fun_arr: .space 3 * 4
	.text
	.global main
main:
	leal	fun1, fun_arr
	movl	$fun2, fun_arr + 4
	movl	$fun3, fun_arr + 8

	call	readi32

	leal	fun_arr(,%eax,4), %ebx
	jmp	*(%ebx)

	// movl 	fun_arr(,%eax,4), %ebx
	// jmp	*%ebx

fun1:
	movl $1, %eax
	call writei32
	call finish

fun2:
	movl $2, %eax
	call writei32
	call finish

fun3:
	movl $4, %eax
	call writei32
	call finish
