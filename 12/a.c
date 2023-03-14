#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void closep(int* p) {
	close(p[0]);
	close(p[1]);
}

void interact(int x, int pnum) {
	if (x > 0) {
		printf("%d\n", x);
		fflush(stdout);
	}
	while(scanf("%d", &x) == 1) {
		fprintf(stderr, "%d %d\n", pnum, x);
		if (x > 0) {
			printf("%d\n", x - 1);
			fflush(stdout);
		} else {
			return;
		}
	}
}

int main() {
	int p1to2[2]; // 0 - read 1 - write
	int p2to1[2];
	pipe(p1to2);
	pipe(p2to1);

	int x = 10;

	if (!fork()) {
		dup2(p1to2[1], 1);
		dup2(p2to1[0], 0);
		closep(p1to2);
		closep(p2to1);
		interact(x, 1);
		exit(0);
	}
	if (!fork()) {
		dup2(p2to1[1], 1);
		dup2(p1to2[0], 0);
		closep(p2to1);
		closep(p1to2);
		interact(0, 2);
		exit(0);
	}
	closep(p1to2);
	closep(p2to1);
	wait(NULL);
	wait(NULL);
}