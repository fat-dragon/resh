#include "resh.h"

int
main(int argc, char *argv[])
{
	argv[0] = "/usr/bin/man";
	return(spawn(argc, argv));
}
