#include <stdlib.h>
#include <stdio.h>

typedef struct {
	unsigned hours : 5;
	unsigned minutes : 6;
	unsigned seconds : 6;
} time;

int main() {
	printf("%lu\n", sizeof(time));
}