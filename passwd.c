#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *args[] = { "/usr/local/heimdal/bin/kpasswd", NULL };
	return(spawn(NELEM(args), args));
}