#include <stdio.h>
#define O 1
#define I int
#define C char
#define R return
#define P putchar
typedef I i;typedef C c;
I main(){c*s="\033[2J\033[H";i j=O;O_:P(s[j-1]);j++;if(s[j-2])goto O_;R O;}
