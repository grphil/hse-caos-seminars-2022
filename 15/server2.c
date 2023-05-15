#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/epoll.h>

int create_listener(char* service) {
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
		.ai_flags = AI_PASSIVE,
	};
	struct addrinfo* result;

	int err = getaddrinfo(NULL, service, &hints, &result);

	int sock = -1;
	for (struct addrinfo* ai = result; ai != NULL; ai = ai->ai_next) {
		sock = socket(ai->ai_family, ai->ai_socktype, 0);

		if (sock < 0) {
			perror("socket");
			continue;
		}

		if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
			perror("bind");
			close(sock);
			sock = -1;
			continue;
		}

		if (listen(sock, SOMAXCONN) < 0) {
			perror("listen");
			close(sock);
			sock = -1;
			continue;
		}

		break;
	}

	freeaddrinfo(result);

	return sock;
}

/*
new connection
connection update
*/

int main(int argc, char** argv) {
	int sock = create_listener(argv[1]);

	if (sock < 0) {
		return 1;
	}

	int epollfd = epoll_create1(0);

	struct epoll_event add_sock = {.events = EPOLLIN, .data.fd = sock};
	epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &add_sock);

	while (true) {
		struct epoll_event event;

		epoll_wait(epollfd, &event, 1, -1);

		if (event.data.fd == sock) {
			int conn = accept(sock, NULL, NULL);

			struct epoll_event add_conn = {.events = EPOLLIN, .data.fd = conn};
			epoll_ctl(epollfd, EPOLL_CTL_ADD, conn, &add_conn);
		} else {
			char buf[100];
			int sz = read(event.data.fd, buf, 100);
			if (sz == 0) {
				close(event.data.fd);
			} else {
				printf("read %d bytes, %s\n", sz, buf);
			}
		}
		
	}
}