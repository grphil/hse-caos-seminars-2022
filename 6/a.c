#include <stdlib.h>
#include <stdio.h>

struct vector {
	size_t size;
	size_t capacity;
	int* v;

	void (*push_back)(struct vector* this, int a);
};

typedef struct vector vector;

void vector_push_back(struct vector* this, int a) {
	if (this->size == this->capacity) {
		size_t new_cap = this->capacity * 2 + 1;
		int* new_v = realloc(this->v, new_cap * sizeof(*new_v));
		if (new_v == NULL) {
			exit(-1);
		}
		this->v = new_v;
		this->capacity = new_cap;
	}
	this->v[this->size] = a;
	this->size++;
}

vector vector_new() {
	return (vector){.size = 0, .capacity = 0, .v = NULL, .push_back = vector_push_back};
}

int main() {
	vector v = vector_new();
	v.push_back(&v, 1);
	v.push_back(&v, 3);
	v.push_back(&v, 2);
	printf("%d %d %d %zu %zu\n", v.v[0], v.v[1], v.v[2], v.size, v.capacity);
	v.push_back(&v, 2);
	printf("%d %d %d %zu %zu\n", v.v[0], v.v[1], v.v[2], v.size, v.capacity);
}
