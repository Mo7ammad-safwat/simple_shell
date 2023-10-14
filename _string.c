#include "all.h"

/**
 * _strtok - Split a string into tokens.
 *
 * @str: The string to be split.
 * @delim: The delimiter used to split the string.
 *
 * Return: A pointer to the next token or NULL if there are no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
	{
		last = str;
	}
	else if (last == NULL)
	{
		return (NULL);
	}

	token = last;

	while (*last != '\0')
	{
		if (*delim == *last)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}

	last = NULL;
	return (token);
}

/**
 * _strdup - Duplicate a string.
 *
 * @args: Pointer to parameter structure.
 * @str: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string, or NULL if memory allocation fails.
 */
char *_strdup(para *args, char *str)
{
	if (!str)
	{
		return (NULL);
	}

	int len = _strlen(str);
	char *copy = _malloc(args, len + 1);

	for (int i = 0; i <= len; i++)
	{
		copy[i] = str[i];
	}

	return (copy);
}

/**
 * _strncmp - Compare two strings up to a certain number of characters.
 *
 * @str1: The first string.
 * @str2: The second string.
 * @n: The maximum number of characters to compare.
 *
 * Return: 0 if the strings are equal, a positive value if str1 is greater, and a negative
 * value if str2 is greater.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n-- && (*str1 != '\0' || *str2 != '\0'))
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}

	return (0);
}

/**
 * _strchr - Locate a character in a string.
 *
 * @str: The string to search in.
 * @c: The character to locate.
 *
 * Return: A pointer to the first occurrence of the character in the string, or NULL if the
 * character is not found.
 */
char *_strchr(char *str, char c)
{
	int i = 0;

	while (i < _strlen(str))
	{
		if (str[i] == c)
		{
			return (str + i);
		}
		i++;
	}

	return (NULL);
}

/**
 * _strncat - Concatenate two strings, appending at most n characters from src.
 *
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to append from src.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = _strlen(dest), i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}

	dest[dest_len + i] = '\0';
	return (dest);
}
