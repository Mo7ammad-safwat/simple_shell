#include "all.h"

/**
 * cd - Change directory.
 * @args: Pointer to a structure containing various parameters.
 *
 * Return: 1 if the command is "cd", 0 if not.
 */
int cd(para *args)
{
	char *dest, *line = args->line;

	if (!_strcmp(line, "cd"))
	{
		if (args->n_token == 1)
			dest = _get_env(args->envp, "HOME", 4);
		else
		{
			line += 3;

			if (!_strcmp(line, "-"))
			{
				dest = args->old_pwd;
				write(1, dest, _strlen(dest));
				write(1, "\n", 1);
			}
			else
				dest = line;
		}

		if (chdir(dest) == -1)
		{
			_printf("%s: %i: cd: can't cd to %s\n", args->shell_name, args->count, dest);
			args->status = 2;
		}
		else
		{
			free(args->old_pwd);
			args->old_pwd = _strdup(args, &((*(args->pwd))[4]));
			if (!args->old_pwd)
				free_exit(args);

			change_pwd(args);
			args->status = 0;
		}

		return (1);
	}

	return (0);
}

/**
 * change_pwd - Change PWD environment variable.
 * @args: Pointer to a structure containing various parameters.
 */
void change_pwd(para *args)
{
	char buffer[250];
	char *pwd = _malloc(args, 256);

	getcwd(buffer, 250);

	pwd[0] = '\0';
	_strcat(pwd, "PWD=");
	_strcat(pwd, buffer);

	free(*(args->pwd));
	*(args->pwd) = pwd;
}

/**
 * get_PWD - Get and update PWD environment variable.
 * @args: Pointer to a structure containing various parameters.
 *
 * Return: Pointer to PWD environment variable.
 */
char **get_PWD(para *args)
{
	int i;
	char *pwd = NULL;

	for (i = 0; args->envp[i] != NULL; i++)
	{
		if (_strncmp(args->envp[i], "PWD", 3) == 0)
		{
			pwd = _strdup(args, args->envp[i]);
			args->envp[i] = pwd;
			return (&(args->envp[i]));
		}
	}

	return (NULL);
}

/**
 * free_exit - Free memory and exit program.
 * @args: Pointer to a structure containing various parameters.
 */
void free_exit(para *args)
{
	if (args->line)
		free(args->line);
	if (args->path)
		free(args->path);
	if (args->pwd)
		free(*(args->pwd));
	if (args->old_pwd)
		free(args->old_pwd);

	exit(255);
}

/**
 * _malloc - Custom memory allocation function.
 * @args: Pointer to a structure containing various parameters.
 * @size: Size of memory block to allocate.
 *
 * Return: Pointer to the allocated memory block.
 */
char *_malloc(para *args, int size)
{
	char *buff = malloc(size);

	if (!buff)
		free_exit(args);

	return (buff);
}
