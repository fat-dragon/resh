#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "resh.h"

const char *world = "/fat-dragon/lib/resh/world";

static char *room;
static char *north;
static char *south;
static char *east;
static char *west;
static char *up;
static char *down;

static void
stare(const char *at)
{
	char descfile[1024];
	char *args[] = { "pg", descfile, NULL };

	if (at == NULL) {
		printf("You are nowhere to see anything.\n");
		return;
	}
	snprintf(descfile, sizeof descfile, "%s/%s/desc", world, at);
	if (access(descfile, R_OK) < 0) {
		printf("You see nothing.\n");
		return;
	}
	spawn(NELEM(args), args);
}

static const char *
directionor(const char *d, const char *def)
{
	if (STREQ(d, "north"))
		return north;
	if (STREQ(d, "south"))
		return south;
	if (STREQ(d, "east"))
		return east;
	if (STREQ(d, "west"))
		return west;
	if (STREQ(d, "up"))
		return up;
	if (STREQ(d, "down"))
		return down;
	return def;
}

static void
look(int argc, char *argv[])
{
	const char *d;

	if (argc == 1) {
		if (room == NULL) {
			printf("You are nowhere to see anything.\n");
			return;
		}
		stare(room);
		return;
	}
	if (argc != 2) {
		printf("...I don't understand what you want to look at.\n");
		return;
	}
	d = argv[1];
	stare(directionor(d, NULL));
}

static void
navreset()
{
	free(room);
	room = NULL;
	free(north);
	north = NULL;
	free(south);
	south = NULL;
	free(east);
	east = NULL;
	free(west);
	west = NULL;
	free(up);
	up = NULL;
	free(down);
	down = NULL;
}

static char *
estrdup(const char *s)
{
	char *p;

	p = strdup(s);
	if (p == NULL) {
		fprintf(stderr, "Panic zero.  Rebooting...\n");
		exit(1);
	}

	return p;
}

static void
gotoroom(const char *dest)
{
	FILE *fp;
	char roomdir[1024];
	char metafile[1024];
	char line[1024];

	snprintf(roomdir, sizeof roomdir, "%s/%s", world, dest);
	if (access(roomdir, X_OK) < 0) {
		fprintf(stderr, "You can't go in there!\n");
		return;
	}
	snprintf(metafile, sizeof metafile, "%s/meta", roomdir);
	fp = fopen(metafile, "r");
	if (fp == NULL) {
		fprintf(stderr, "You see a roadblock ahead.\n");
		return;
	}
	navreset();
	room = estrdup(dest);
	while (fgets(line, sizeof line, fp) != NULL) {
		const char *c, *d;
		struct rcommand *cmd = resh_parse(line);
		if (cmd->argc != 2) {
			fprintf(stderr, "Strange number of tokens; meta!?\n");
			continue;
		}
		c = cmd->argv[0];
		d = cmd->argv[1];
		if (STREQ(c, "north"))
			north = estrdup(d);
		if (STREQ(c, "south"))
			south = estrdup(d);
		if (STREQ(c, "east"))
			east = estrdup(d);
		if (STREQ(c, "west"))
			west = estrdup(d);
		if (STREQ(c, "up"))
			up = estrdup(d);
		if (STREQ(c, "down"))
			down = estrdup(d);
	}
	fclose(fp);
	stare(dest);
}

static void
teleport(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Can't teleport to nowhere!\n");
		return;
	}
	if (argc > 2) {
		fprintf(stderr, "Can't teleport to more than one place at once!\n");
		return;
	}
	gotoroom(argv[1]);
}

static void
cardinal(int argc, char *argv[])
{
	if (argc != 1) {
		printf("Huh!?\n");
		return;
	}
	gotoroom(directionor(argv[0], NULL));
}

int
navigate(const char *c, int argc, char *argv[])
{

	if (STREQ(c, "look")) {
		look(argc, argv);
		return 1;
	}
	if (STREQ(c, "teleport") || STREQ(c, "cd")) {
		teleport(argc, argv);
		return 1;
	}
	if (STREQ(c, "north") ||
	    STREQ(c, "south") ||
	    STREQ(c, "east") ||
	    STREQ(c, "west") ||
	    STREQ(c, "up") ||
	    STREQ(c, "down")) {
		cardinal(argc, argv);
		return 1;
	}

	return 0;
}
