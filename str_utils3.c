#include "shell.h"

/**
 *  _exit_atoi - atoi for exit status
 *
 *  @str: String passed through
 *
 *
 *  Return: Exit status int or -1 on failure
 */

int _exit_atoi(char *str)
{
	int result = 0, index = 0, int_max = 2147483647;

	/* Is negative */
	if (str[index] == '-')
	{
		return (1);
	}

	while (str[index] != '\0')
	{
		if (_isdigit(str[index]) == 1)
		{
			result = result * 10 + str[index] - '0';
		}
		else
		{
			return (1);
		}
		index++;
	}

	if (result > int_max)
	{
		return (1);
	}
	else
		return (result);
}



/**
 *  _isdigit - Finds if char is a digit or not
 *
 *  @str: Character passed in
 *
 *  Return: 1 for digit, 0 if not
 */

int _isdigit(char str)
{
	if (str >= '0' && str <= '9')
	{
		return (1); /* Success */
	}
	return (0);
}

/**
 * _strcpy - Prints a string
 * @dest: Destination
 * @src: Source
 * Return: Always dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
