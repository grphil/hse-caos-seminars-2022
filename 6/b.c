#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	char* s;
	size_t size;
} string;

string read_string() {
	string s = {.s = calloc(1, sizeof(char)), .size = 0};
	char c;
	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			if (s.size > 0) {
				break;
			} else {
				continue;
			}
		}
		char* new_s = realloc(s.s, s.size + 2);
		s.s = new_s;
		s.s[s.size++] = c;
	}
	s.s[s.size] = '\0';
	return s;
}

void remove_string(string* s) {
	free(s->s);
	s->s = NULL;
	s->size = 0;
}

int main() {
	string s1 = read_string();
	string s2 = read_string();
	string s3 = read_string();
	printf("%s, %s, %s\n", s1.s, s2.s, s3.s);
	remove_string(&s1);
	remove_string(&s2);
	remove_string(&s3);
}