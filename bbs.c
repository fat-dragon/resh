#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *args[] = { "/fat-dragon/bin/notes", "fat-dragon", NULL };
	return(spawn(NELEM(args)-1, args));
}
