#include "resh.h"

int
main(int argc, char *argv[])
{
	argv[0] = "/usr/local/bin/mc";
	return(spawn(argc, argv));
}
