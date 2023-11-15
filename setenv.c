
#include "shell.h"
/**
 * call_unsetenv - Unsets enviorments variabls
 * @env: Enviorment variables
 * @str: User input
 * Return: Always 1
 */

int call_unsetenv(char **env, char **str)
{
	int i = 0;

	if (str == NULL || str[1] == NULL || str[1][0] == '\0')
	{
		errno = EINVAL;
		perror("hsh");

		return (1);
	}

	i = find_env_var(env, str[1]);

	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}

	return (1);
}

/**
 *  call_setenv - setenv builtin
 *
 *  @env: Environment variable
 *
 *  @str: Double pointer string
 *
 *  Return: Integer
 */


int call_setenv(char **env, char **str)
{
	int i = 0, total = 0, len = 0;
	char *copy = NULL, *new = NULL;

	printf("%s\n", str[1]);
	printf("%s\n", env[0]);

	i = find_env_var(env, str[1]);

	printf("%s\n", env[i]);
	if (i != 0 && str[3] != 0)
	{
		len = _strlen(env[i]);
		call_unsetenv(env, str);

		total = (_strlen(str[1]) + _strlen(str[2]) + 2);

		new = malloc(1024);
		copy = malloc(total);

		new = _strcat(str[1], "=");
		copy = _strcat(new, str[2]);
		_realloc(env[i], len, _strlen(copy));
		env[i] = copy;
	}

	return (1);
}
