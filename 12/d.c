#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	sigset_t signals, old;
	sigemptyset(&signals);
	sigaddset(&signals, SIGINT);

	while(1) {
		sigprocmask(SIG_BLOCK, &signals, &old);
		printf("qwertty\n");
        sleep(3);
		printf("asdfg\n");
		sigprocmask(SIG_UNBLOCK, &signals, &old);
	}
}