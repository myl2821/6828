#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	int i;

	if (argc == 1)
		cprintf("rm file[...]\n");
	else
		for (i = 1; i < argc; i++) {
			remove(argv[i]);
		}
}
