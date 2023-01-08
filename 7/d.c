#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>

jmp_buf *ebuf;
char err_msg[100];

#define try do { \
	jmp_buf env_buf; \
	jmp_buf *old_buf = ebuf; \
	ebuf = &env_buf; \
	if (setjmp(env_buf) == 0) {

#define catch ebuf = old_buf; \
	} else { \
		ebuf = old_buf;

#define endtry }} while(0);

void throw(char* err) {
	strcpy(err_msg, err);
	longjmp(*ebuf, 1);
}

char* get_err() {
	return err_msg;
}

int main() {
	try {
		printf("start\n");
		try {
			printf("start2\n");
			throw("228");
		} catch {
			printf("got err 2\n");
			throw("error 282");
		} endtry
		throw("error 1337");
		printf("no_show");
	} catch {
		printf("%s\n", get_err());
	} endtry
}