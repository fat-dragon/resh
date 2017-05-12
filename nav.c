#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "resh.h"

const char *world = "/fat-dragon/lib/resh/world";

static void
stare(const char *at)
{
	char descfile[1024];
	char navfile[1024];
	char *args[] = { "pg", descfile, navfile, NULL };
	int nargs = NELEM(args) - 1;

	if (at == NULL) {
		printf("You are nowhere to see anything.\n");
		return;
	}
	snprintf(descfile, sizeof descfile, "%s/%s/desc", world, at);
	if (access(descfile, R_OK) < 0) {
		printf("You see nothing.\n");
		return;
	}
	snprintf(navfile, sizeof navfile, "%s/%s/navdesc", world, at);
	if (access(navfile, R_OK) < 0) {
		nargs--;
		args[nargs] = NULL;
	}
	spawn(nargs, args);
}

static void
look(int argc, char *argv[])
{
	const char *room = getvar("room");
	const char *d = NULL;

	if (argc > 3 || (argc == 3 && !STREQ(argv[1], "at"))) {
		warnx("...I don't understand what you want to look at.");
		return;
	}
	if (argc == 3)
		d = argv[2];
	if (argc == 2)
		d = argv[1];
	if (d != NULL)
		room = getvar(d);
	if (room == NULL)
		room = d;
	if (room == NULL) {
		if (argc == 1)
			warnx("You are nowhere to see anything.");
		else
			warnx("There's nothing there to look at.");
		return;
	}
	stare(room);
}

static void
navreset()
{
	unsetvar("room");
	unsetvar("north");
	unsetvar("south");
	unsetvar("east");
	unsetvar("west");
	unsetvar("up");
	unsetvar("down");
	unsetvar("notesfiles");
}

static int
knowntok(const char *c)
{
	const char *ts[] = { "north", "south", "east", "west", "up", "down", "notesfiles" };

	for (int i = 0; i < NELEM(ts); i++)
		if (STREQ(c, ts[i]))
			return 1;
	return 0;
}

static void
gotoroom(const char *dest)
{
	FILE *fp;
	char roomdir[1024];
	char metafile[1024];
	char line[1024];

	if (dest == NULL) {
		warnx("You can't get there form here.");
		return;
	}
	snprintf(roomdir, sizeof roomdir, "%s/%s", world, dest);
	if (access(roomdir, X_OK) < 0) {
		warnx("You can't go in there!");
		return;
	}
	snprintf(metafile, sizeof metafile, "%s/meta", roomdir);
	fp = fopen(metafile, "r");
	if (fp == NULL) {
		warnx("You see a roadblock ahead.");
		return;
	}
	navreset();
	setvar("room", dest);
	while (fgets(line, sizeof line, fp) != NULL) {
		struct rcommand *cmd = resh_parse(line);
		if (cmd->argc != 2) {
			warnx("Strange number of tokens; meta file!?");
			continue;
		}
		if (!knowntok(cmd->argv[0]))
			continue;
		setvar(cmd->argv[0], cmd->argv[1]);
		if (!STREQ(cmd->argv[1], getvar(cmd->argv[0])))
			errx(1, "Bad value! expected '%s', got '%s'\n",
			    cmd->argv[1], getvar(cmd->argv[0]));
	}
	fclose(fp);
	if (getvar("notesfiles") == NULL)
		setvar("notesfiles", "fat-dragon");
	stare(dest);
}

static void
teleport(int argc, char *argv[])
{
	if (argc < 2) {
		warnx("Can't teleport to nowhere!");
		return;
	}
	if (argc > 2) {
		warnx("Can't teleport to more than one place at once!");
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
	gotoroom(getvar(argv[0]));
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
