#include <unistd.h>
#include <stdio.h>

int main() {
x:
	fork();
	printf("a\n");
	goto x;
}