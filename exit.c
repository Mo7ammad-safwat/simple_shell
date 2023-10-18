#include "shell.h"
/**
 * handle_exit - function that terminate prog
 * user input "exit".
 * @cmd: the string to be read
 * Return: 0
 *
 */
void handle_exit(char *cmd)
{
	if (_strcmp("exit", cmd) == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}
}
