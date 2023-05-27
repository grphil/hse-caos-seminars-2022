#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

#include <sys/syscall.h>
#include <linux/futex.h>
#include <unistd.h>
#include <stdint.h>

int counter = 0;
int data = 0;

typedef _Atomic uint32_t mutex;

void futex_wait(mutex* s, uint32_t old) {
	syscall(SYS_futex, s, FUTEX_WAIT_PRIVATE, old, NULL, NULL, NULL);
}

void futex_wake(mutex* s) {
	syscall(SYS_futex, s, FUTEX_WAKE_PRIVATE, 1, NULL, NULL, NULL);
}

void mutex_lock(mutex* s) {
	// return;
    while (atomic_exchange(s, 1) != 0) { 
    	futex_wait(s, 1); 
    }
}

void mutex_unlock(mutex* s) {
	// return;
	atomic_store(s, 0);
	futex_wake(s);
}

mutex lock;

void* threadFunc(void* arg) {
    for (int i = 0; i < 1000000; i++) {
    	mutex_lock(&lock);
    	data = 1;
    	counter += data;
    	mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
	pthread_t threadId;

	int err = pthread_create(&threadId, NULL, &threadFunc, NULL);

	if (err) {
		printf("%s\n", strerror(err));
		return 0;
	}
	
	for (int i = 0; i < 1000000; i++) {
		mutex_lock(&lock);
		data = 2;
		counter += data;
		mutex_unlock(&lock);
	}

	pthread_join(threadId, NULL);
	printf("%d\n", counter);
}