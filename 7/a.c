#include <stdlib.h>
#include <stdio.h>

int main() {
	fprintf(stdout, "%s\n", "228");
	FILE* a = fopen("b.txt", "w");
	double s[3] = {1, 2, 3};
	int x = 228;
	fprintf(, "%s\n", );
	fwrite(s, sizeof(s[0]), 3, a);
	fwrite(&x, sizeof(x), 1, a);
	fclose(a);
}