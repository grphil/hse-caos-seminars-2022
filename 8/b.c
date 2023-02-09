#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum {
	BUF_SIZE = 4096,
};


typedef struct F {
	int fd;
	char buf[BUF_SIZE];
	ssize_t size;
	ssize_t pos;
} F;

F* ropen(char* path) {
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		return NULL;
	}
	F* f = calloc(1, sizeof(F));
	f->fd = fd;
	return f;
}

void rclose(F* f) {
	close(f->fd);
	free(f);
}

bool readBuf(F* f) {
	f->pos = 0;
	f->size = 0;
	ssize_t n = read(f->fd, f->buf, BUF_SIZE);
	if (n <= 0) {
		return false;
	}
	f->size = n;
	return true;
}

char rget(F* f) {
	if (f->size == f->pos) {
		if (!readBuf(f)) {
			return '\0';
		}
	}
	return f->buf[f->pos++];
}

bool rlseek(F* f, size_t size) {
	off_t n = lseek(f->fd, size, SEEK_SET);
	if (n == -1) {
		return false;
	}
	readBuf(f);
	return true;
}

int main() {
	F* f = ropen("a.txt");

	char c;
	while ((c = rget(f)) != '\0') {
		printf("%c", c);
	}
	printf("\n");
	rlseek(f, 4);
	while ((c = rget(f)) != '\0') {
		printf("%c", c);
	}

	rclose(f);
}

