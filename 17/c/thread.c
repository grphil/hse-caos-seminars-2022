#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunc(void* arg) {
	printf("thread start\n");
	fflush(stdout);
	sleep(2);
	printf("thread end\n");
	fflush(stdout);
	return NULL;
}

int main() {
	pthread_t threadId;

	pthread_create(&threadId, NULL, &threadFunc, NULL);

	sleep(1);
	printf("main function\n");
	fflush(stdout);

	pthread_join(threadId, NULL);
	printf("finished\n");
}