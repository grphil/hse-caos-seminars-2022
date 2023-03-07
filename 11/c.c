#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

int main() {
	char* folder = "./";
	pid_t x = fork();
	if (x == 0) {
		execlp("ls", "ls", "-lh", folder, NULL);
		// If we go here, execlp did not start
		exit(1);
	}
	wait(NULL);
}