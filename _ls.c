#include "resh.h"

int
main(int argc, char *argv[])
{
	argv[0] = "/bin/ls";
	return(spawn(argc, argv));
}
