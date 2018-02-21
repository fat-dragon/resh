#include "resh.h"

int
main(int argc, char *argv[])
{
	argv[0] = "/bin/df";
	return(spawn(argc, argv));
}
