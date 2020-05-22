#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRSIZE 8

char *p;
char str[STRSIZE];
char *q;

void append(char *str, char *app)
{
	strcat(str, app);
}


int main(void)
{
	p = q = str;
	strcpy(str, "hello ");
	append(str, "there");

	printf("str = %s\n", str);
	printf("p   = %s\n", p);
	printf("q   = %s\n", q);
	return 0;
}
