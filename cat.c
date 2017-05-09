#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "resh.h"

static void
cat(int fd)
{
	ssize_t n;
	char buf[2048];

	while ((n = read(fd, buf, sizeof(buf))) > 0)
		write(STDOUT_FILENO, buf, n);
}

int
main(int argc, char *argv[])
{
	int fd;

	if (argc == 1)
		cat(STDIN_FILENO);
	else while (*++argv) {
		if (STREQ(*argv, "-")) {
			cat(STDIN_FILENO);
			continue;
		}
		fd = openr(*argv);
		if (fd < 0) {
			warn("%s: open failed", *argv);
			continue;
		}
		cat(fd);
		close(fd);
	}

	return(EXIT_SUCCESS);
}
