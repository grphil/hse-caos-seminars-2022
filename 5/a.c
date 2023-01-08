#include <stdio.h>
#include <string.h>

typedef struct {
	int x;
	int y;
} a;

int main() { // DD-MM-YYY hh:mm:ss
	a x = {};
	scanf("%d %d", &x.x, &x.y);
	printf("%d %d", x.x, x.y);
}