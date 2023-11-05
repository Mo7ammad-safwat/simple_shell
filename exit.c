#include "shell.h"

/**
 **strncpy - copy a string
 *@dest: the destination for string
 *@src: src string
 *@n: the amount of chars
 *Return: the string
 */
char *strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strncat - concatenates strings
 *@dest: 1st string
 *@src: 2nd string
 *@n: the amount of bytes
 *Return: string
 */
char *strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 **strchr - character in a string
 *@s: string
 *@c: character to look for
 *Return: a pointer
 */
char *strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
