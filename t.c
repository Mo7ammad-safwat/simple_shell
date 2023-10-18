#include "shell.h"
/**
 * _strcmp -  compares two strings
 * @s1: 1st function
 * @s2: 2nd function
 * Return: 1
 */
int _strcmp(char *s1, char *s2)
{
	int cmp = 0;

	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (s1 != s2)
		cmp = *s1 - *s2;

	return (cmp);
}
