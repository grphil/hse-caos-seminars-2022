#include <stdlib.h>
#include <stdio.h>

int main() {
	FILE* a = fopen("a.txt", "r");
	char buf[100];
	int n;
	fscanf(a, "%10s%n", buf, &n);
	printf("%s %d\n", buf, n);
}