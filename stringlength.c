#include "shell.h"
/**
 * _strlen - string length
 * @s: string input
 * Return: char number
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}
