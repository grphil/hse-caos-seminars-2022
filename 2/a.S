	.text
	.global main
main:
	movl $1, %eax // eax = 1
	subl $1, %eax // eax -= 1 ZF = 1 if got zero
	subl $1, %eax // eax -= 1 SF = 1 if got negative number
	// ZF - ноль
	// SF - отрицательное число
	// CF - переполнение unsigned
	// OF - переполнение signed
	movl $2, %ebx
	cmpl %eax, %ebx // ebx - eax 
	// EF - равны
	// N - ключевая буква отрицания
	// GF - больше signed
	// LF - меньше signed
	// AF - больше unsigned
	// BF - меньше unsigned

sdhshfdhjkfs:
	addl $1, %eax
	cmpl %eax, %ebx
	jge sdhshfdhjkfs
	movl $1, %eax
	testl $1, %eax // x = 0b0010 & eax; if x == 0 { ef = true } else {ef = false}


	a 



