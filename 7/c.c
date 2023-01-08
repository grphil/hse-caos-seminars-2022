#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

jmp_buf ebuf;

void f(int a) {
	printf("%d\n", a);
	longjmp(ebuf, a + 1);
}

int main() {
	volatile int c = 0;
	int a = setjmp(ebuf);
	if (a < 5) {
		c++;
		printf("C %d\n", c);
		f(a);
	}
}