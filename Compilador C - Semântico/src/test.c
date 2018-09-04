#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct test_s{
	const int integer;
} test_t;

int main(){
	test_t *test = malloc(sizeof(test_t));
	*(int*)&test->integer = 2;
	printf("%d\n", test->integer );
}
