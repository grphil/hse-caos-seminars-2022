#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node {
	int value;
	struct queue_node* next;
} queue_node;

typedef struct queue {
	queue_node* first;
	queue_node* last;

	int (*get)(struct queue* this);
	void (*pop)(struct queue* this);
	void (*add)(struct queue* this, int a);
} queue;

int queue_get(queue* this) {
	return this->first->value;
}

void queue_pop(queue* this) {
	queue_node* next = this->first->next;
	free(this->first);
	this->first = next;
	if (next == NULL) {
		this->last = NULL;
	}
}

void queue_add(queue* this, int a) {
	queue_node* new_last = calloc(1, sizeof(*new_last));
	new_last->value = a;

	if (this->first == NULL) {
		this->first = new_last;
	} else {
		this->last->next = new_last;
	}

	this->last = new_last;
}

queue* queue_new() {
	queue* q = calloc(1, sizeof(*q));
	q->get = queue_get;
	q->pop = queue_pop;
	q->add = queue_add;
	return q;
}

void destruct_queue(queue* q) {
	while (q->first != NULL) {
		q->pop(q);
	}
	free(q);
}

int main() {
	queue* q = queue_new();
	q->add(q, 1);
	printf("%d\n", q->get(q));
	q->add(q, 2);
	printf("%d\n", q->get(q));
	q->pop(q);
	printf("%d\n", q->get(q));
	q->pop(q);
	q->add(q, 3);
	printf("%d\n", q->get(q));
}
