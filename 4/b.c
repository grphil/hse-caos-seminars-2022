#include <stdio.h>

extern int sumab(int a, int b);

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", sumab(a, b));
}