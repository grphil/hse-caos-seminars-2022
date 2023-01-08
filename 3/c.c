#include <stdio.h>

extern int A;
extern void inc_a(void);

int main(void) {
	scanf("%d", &A);
	inc_a();
	printf("%d\n", A);
}