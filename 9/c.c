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
	char* fname = "b.txt";

	char res[] = "qwertyuiop\nasdfghjkl\nzxcvbnm";

	int fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);

	ftruncate(fd, sizeof(res) - 1);

	char* s = mmap(NULL, sizeof(res) - 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (s == MAP_FAILED) {
		perror("error in mmap");
		return -1;
	}

	memcpy(s, res, sizeof(res) - 1);

	// printf("%.*s\n", (int)st.st_size, s);

	munmap(s, sizeof(res) - 1);
	close(fd);
}