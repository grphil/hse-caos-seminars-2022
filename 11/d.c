#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/wait.h>

int main() {
	char* file = "./c.c";
	pid_t x = fork();
	if (x == 0) {
		int fd = open(file, O_RDONLY, 0);
		dup2(fd, 0); // 0 - file
		close(fd);
		execlp("wc", "wc", "-l", NULL);
		// If we go here, execlp did not start
		exit(1);
	}
	wait(NULL);
}