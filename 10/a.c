#include <dlfcn.h>

#include <stdio.h>
#include <string.h>

int main() {
	void* aa = dlopen("aa", RTLD_NOW);

	if (aa == 0) {
		printf("failed to open\n");
		return 1;
	}

	int (*f)(int, int);

	char buf[100];
	int a, b;
	scanf("%s %d %d", buf, &a, &b);

	f = dlsym(aa, buf);

	if (f == NULL) {
		printf("No func %s found\n", buf);
		return 2;
	}

	int c = f(a, b);
	printf("%d\n", c);
}