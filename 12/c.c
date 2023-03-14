#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t couter = 0; // int

void handler(int signo) {
	if (++couter < 4) {
		printf("recieved %d signals\n", couter);
	} else {
		printf("finishing after signal %d\n", signo);
		exit(0);
	}
}

int main() {

	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;

	sigaction(SIGINT, &sa, NULL);
	while(1) {
		int x;
		scanf("%d", &x);
		printf("sdfsdfsdfs %d\n", x);
		pause();
	}
}