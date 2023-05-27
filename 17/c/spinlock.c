#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

int counter = 0;
int data = 0;

typedef _Atomic int spinlock;

void spin_lock(spinlock* s) {
	while (atomic_exchange(s, 1) == 1) {
		asm volatile ("pause");
	}
}

void spin_unlock(spinlock* s) {
	atomic_store(s, 0);
}

spinlock m;

void* threadFunc(void* arg) {
	for (int i = 0; i < 100000; i++) {
		spin_lock(&m);
		data = 2;
		counter += data;
		spin_unlock(&m);
	}
	return NULL;
}

int main() {
	pthread_t threadId;

	pthread_create(&threadId, NULL, &threadFunc, NULL);

	for (int i = 0; i < 100000; i++) {
		spin_lock(&m);
		data = 1;
		counter += data;
		spin_unlock(&m);
	}

	pthread_join(threadId, NULL);
	printf("%d\n", counter);
}