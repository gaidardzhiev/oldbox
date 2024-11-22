#include <stdio.h>
#include <stdlib.h>

#define c char
#define m main
#define e exit
#define g getwd
#define p printf
#define n pathname

c*g();
m() {
	c n[512];
	g(n);
	p("%s\n",n);
	e(0);
}
