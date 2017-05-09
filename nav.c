#include <string.h>
#include "resh.h"

int
navigate(struct rcommand *cmd)
{
	const char *c = cmd->argv[0];
	if (STREQ(c, "north") ||
	    STREQ(c, "south") ||
	    STREQ(c, "east") ||
	    STREQ(c, "west") ||
	    STREQ(c, "up") ||
	    STREQ(c, "down")) {
		return 1;
	}

	if (STREQ(c, "teleport") || STREQ(c, "cd")) {
		return 1;
	}

	return 0;
}
