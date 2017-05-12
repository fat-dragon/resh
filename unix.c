#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *args[] = { "/usr/local/bin/bash", "-l", NULL };
	return(spawn(NELEM(args)-1, args));
}
