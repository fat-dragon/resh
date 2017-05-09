#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *args[] = { "/usr/games/fortune", NULL };
	return(spawn(NELEM(args), args));
}
