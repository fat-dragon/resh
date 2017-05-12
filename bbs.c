#include <stddef.h>
#include "resh.h"

int
main(int argc, char *argv[])
{
	char *bbs = getvar("notesfiles");
	if (bbs == NULL)
		bbs = "*";
	char *args[] = { "/fat-dragon/bin/notes", bbs, NULL };
	return(spawn(NELEM(args)-1, args));
}
