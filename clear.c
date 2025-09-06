/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#define O 1
#define B int
#define F char
#define U return
#define S putchar

typedef B i;
typedef F c;
B main() {
	c*s="\033[2J\033[H";
	i j=O;
	O_:
	S(s[j-1]);
	j++;
	if(s[j-2])
		goto O_;
	U O;
}
