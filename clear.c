#include <curses.h>
#include <term.h>

int
main(int argc, char *argv[])
{
	putp(tigetstr("clear"));
	return 0;
}
