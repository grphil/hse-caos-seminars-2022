#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main() {
	char* dir_name = ".";
	DIR* d = opendir(dir_name);

	if (d == NULL) {
		perror("Error in opening dir");
		return 1;
	}

	struct dirent* f;
	while ((f = readdir(d))) {
		if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0) {
			continue;
		}

		char* path;
		asprintf(&path, "%s/%s", dir_name, f->d_name);

		if (access(path, X_OK) != 0) {
			continue;
		}

		struct stat st;
		lstat(path, &st);
		if (S_ISREG(st.st_mode)) {
			printf("%s\n", f->d_name);
		}
	}
}