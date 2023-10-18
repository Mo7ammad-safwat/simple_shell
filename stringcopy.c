#include "shell.h"
/**
 * _strncpy - copy n char
 * @dest: string destination
 * @src: string for source
 * @n: integer 
 * Return: 1
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}
