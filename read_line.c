#include "shell.h"

/**
 * read_line - Reads args with getline
 *
 * Return: void
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	int i = 0;

	i = getline(&line, &bufsize, stdin);

	if (i == EOF)
	{
		if ((isatty(STDIN_FILENO)) == 1)
			write(1, "\n", 1);
		exit(0);
	}
	return (line);
}
