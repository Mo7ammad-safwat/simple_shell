#include "shell.h"
/**
 * _strcpy - copy the string
 * @dest: destination string
 * @src: arg's source
 * Return: value of string
 */
char *_strcpy(char *dest, char *src)
{
	int i, len = 0;

	while (src[len] != '\0')
	{
		len++;
	}
	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
