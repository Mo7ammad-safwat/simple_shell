#include "shell.h"

/**
 * call_env - Built in function for env
 *
 * @env: Double char pointer
 *
 * Return: Integer
 */

int call_env(char **env)
{
	int i = 0;
	int len = 0;
	char *copy = malloc(8192);

	while (env[i] != NULL)
	{
		len = _strlen(env[i]);
		copy = _strdup(env[i]);

		write(STDOUT_FILENO, copy, len + 1);
		write(1, "\n", 1);
		free(copy);
		i++;
	}
	return (1);
}
