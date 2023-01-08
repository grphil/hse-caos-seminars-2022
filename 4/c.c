#include <stdio.h>

extern int calc_stack(void);

int rec(int a) {
	if (a == 0) {
		return calc_stack();
	} else {
		return rec(a - 1);
	}
}

int main(void) {
	int a;
	scanf("%d", &a);
	int c = rec(a);
	printf("%d\n", c);
}