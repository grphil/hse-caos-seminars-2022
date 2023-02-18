#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() {
	char* fname = "a.txt";

	int fd = open(fname, O_RDONLY, 0);

	struct stat st;
	fstat(fd, &st);

	char* s = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (s == MAP_FAILED) {
		perror("error in mmap");
		return -1;
	}

	printf("%.*s\n", (int)st.st_size, s);

	munmap(s, st.st_size);
	close(fd);
}