#include <ctype.h>
#include <stdio.h>

void mul(uint64_t a, uint64_t b, uint64_t *ra, uint64_t *rb) {
	asm volatile (
		"mulq %%rcx"
		: "=a" (*ra)
		, "=d" (*rd)
		: "a" (a)
		, "c" (b)
	)
}

