#include "shell.h"
/**
 * _strncmp - compares 1st str and 2nd str
 * @str1: 1st string compared
 * @str2: 2nd string compared
 * @n: number of bytes checked
 * Return:  0 string are not equal
 * 0 is str1 is equal to str2
 */

int _strncmp(char *str1, char *str2, int n)
{
	if (!n)
		return (0);
	if (*str1 == *str2)
		return (*str1 ? _strncmp(str1 + 1, str2 + 1, n - 1) : 0);
	if (*str1)
		return (1);
	if (*str2)
		return (-1);
	return (*str1 - *str2);
}
