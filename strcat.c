#include "shell.h"
/**
 * _strcat - This function appends the source string to the destination string
 * @dest: string destination
 * @src: string source
 * Return: 1
 */
char *_strcat(char *dest, char *src)
{
	int len = 0, lend = 0, j;

	while (src[len] != '\0')
	{
		len++;
	}
	while (dest[lend] != '\0')
	{
		lend++;
	}
	for (j = 0; j < len; j++)
	{
		dest[lend + j] = src[j];
	}
	dest[lend + len] = '\0';
	return (dest);
}
