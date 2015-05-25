#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	int i;

	if (argc == 1)
		cprintf("touch filename[...]\n");
	else
		for (i = 1; i < argc; i++) {
			open(argv[i], O_CREAT);
		}
}
