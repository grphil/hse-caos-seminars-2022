#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char** argv) {
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};
	struct addrinfo* result;

	int err = getaddrinfo(argv[1], argv[2], &hints, &result);

	if (err) {
		perror("getaddrinfo");
		return 1;
	}

	int fd = socket(PF_INET, SOCK_STREAM, 0);

	bool connected = false;

	for (struct addrinfo* a = result; a != NULL; a = a->ai_next) {
		if (connect(fd, a->ai_addr, a->ai_addrlen) >= 0) {
			connected = true;
			break;
		}
	}

	freeaddrinfo(result);

	FILE* fout = fdopen(fd, "w");

	int x;
	while (scanf("%d", &x)) {
		fprintf(fout, "%d\n", x);
		fflush(fout);
	}

	fclose(fout);
}