#include "all.h"

/**
 * _strlen - Calculate the length of a string.
 *
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != 0)
	{
		i++;
	}

	return (i);
}

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: The concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = _strlen(dest), i = 0;

	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strcmp - Compare two strings.
 *
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: The difference between the first differing characters.
 */
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] != 0 || str2[i] != 0)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/**
 * rev_cmp - Compare two strings in reverse order.
 *
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 1 if the second string is a reverse substring of the first, 0 otherwise.
 */
int rev_cmp(char *str1, char *str2)
{
	int len1 = (_strlen(str1) - 1), len2 = (_strlen(str2) - 1), i;

	if (len2 > len1)
		return (0);
	for (i = len2; i >= 0; i--)
	{
		if (str1[len1] != str2[i])
			return (0);
		len1--;
	}
	return (1);
}

/**
 * tostring - Convert an integer to a string.
 *
 * @str: The output string.
 * @num: The input integer.
 */
void tostring(char *str, int num)
{
	int i, len = 0, n = num;

	if (!n)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	while (n)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		str[len - (i + 1)] = num % 10 + '0';
		num /= 10;
	}
	str[len] = '\0';
}
