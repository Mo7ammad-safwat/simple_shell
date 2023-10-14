#include "all.h"

/**
 * _realloc - Reallocate memory block.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size of the old memory block.
 * @new_size: Size of the new memory block.
 *
 * Return: Pointer to the newly allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *buffer;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	buffer = malloc(new_size);

	if (buffer == NULL)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (buffer);

	for (i = 0; i < old_size && i < new_size; i++)
	{
		buffer[i] = ((char *)ptr)[i];
	}

	free(ptr);
	return (buffer);
}

/**
 * _atoi - Convert a string to an integer.
 * @str: The string to convert.
 *
 * Return: The converted integer.
 */
int _atoi(char *str)
{
	int i = (_strlen(str) - 1), j, num = 0, power = 1;

	for (j = 0; j <= i; j++)
	{
		if (str[i - j] > 47 && str[i - j] < 58)
		{
			num += (str[i - j] - 48) * power;
			power *= 10;
		}
		else
			return  (-1);
	}

	return  (num);
}

/**
 * _env - Print environment variables.
 * @args: Pointer to a structure containing various parameters.
 *
 * Return: 1 if the command is "env", 0 otherwise.
 */
int _env(para *args)
{
	int i;

	if (rev_cmp(args->line, "env"))
	{
		for (i = 0; args->envp[i] != NULL; i++)
		{
			write(1, args->envp[i], _strlen(args->envp[i]));
			write(1, "\n", 1);
		}

		args->status = 0;
		return (1);
	}

	return (0);
}

/**
 * _get_env - Get the value of an environment variable.
 * @envp: Array of environment variables.
 * @env: The environment variable to retrieve.
 * @len: The length of the environment variable string.
 *
 * Return: Pointer to the value of the environment variable.
 */
char *_get_env(char **envp, char *env, int len)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], env, len) == 0)
			return (&(envp[i][len + 1]));
	}

	return (NULL);
}

/**
 * handle_realloc - Reallocate memory buffer if needed.
 * @args: Pointer to a structure containing various parameters.
 * @buffer: Pointer to the buffer to be reallocated.
 * @buffer_size: Pointer to the size of the buffer.
 * @extra: Extra size to be added to the buffer.
 * @max: Maximum size of the buffer.
 *
 * Return: Pointer to the reallocated buffer.
 */
char *handle_realloc(para *args, char *buffer, int *buffer_size, int extra, int max)
{
	if (*buffer_size <= max)
	{
		buffer = _realloc(buffer, *buffer_size, *buffer_size + extra);

		if (buffer == NULL)
		{
			free_exit(args);
		}

		*buffer_size += extra;
	}

	return (buffer);
}
