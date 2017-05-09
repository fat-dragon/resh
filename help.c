#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *args[] = { "pg", "/fat-dragon/lib/resh/resh-help", NULL };
	return(spawn(NELEM(args), args));
}
