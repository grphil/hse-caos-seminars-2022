#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

int main() {
	pid_t x = fork();
	if (x == 0) { // child
		printf("child\n");
		exit(0);
	} else {
		wait(NULL);
		printf("parent, child id: %d\n", x);
	}
}