#include "shell.h"

/**
 * WhoAmI - It's a seeeecret
 *
 * Return: Text fi
 */

int WhoAmI(void)
{
	int txt_file, total, read_status;
	size_t letters = 1000;
	char *filename = "WhoAmI.txt";
	char buffer[BUFFERSIZE];

	if (filename == NULL)
		return (0);
	txt_file = open(filename, O_RDONLY);
	if (txt_file == -1)
	{
		return (0);
	}

	total = 0;
	read_status = 1;

	while (letters > BUFFERSIZE && read_status != 0)
	{
		read_status = read(txt_file, buffer, BUFFERSIZE);
		write(STDOUT_FILENO, buffer, read_status);
		total += read_status;
		letters -= BUFFERSIZE;
	}
	read_status = read(txt_file, buffer, letters);
	write(STDOUT_FILENO, buffer, read_status);
	total += read_status;
	close(txt_file);

	return (0);
}
