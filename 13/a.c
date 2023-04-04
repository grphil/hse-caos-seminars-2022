#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int a;

void handler(int signo) {
	a++;
}

int main() {
	sigset_t signals, signals2;
	sigemptyset(&signals);
	sigaddset(&signals, SIGINT);
	sigprocmask(SIG_BLOCK, &signals, NULL);

	struct sigaction sa;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;

	sigaction(SIGINT, &sa, NULL);

	while(1) {
		sigsuspend(&signals2);
		int x;
		scanf("%d", &x);
		printf("%d\n", x + a);
	}
}