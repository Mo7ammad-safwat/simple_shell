#include "shell.h"

/**
 * _strlen - returns the length of a string
 *
 * @str: arg str
 *
 * Return: String length
 */

int _strlen(char *str)
{
	int length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
		return (length);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */


int _putchar(char c)
{
	return (write(1, &c, 1));
}


/**
 * _puts -  prints a string
 *
 * @str: arg s
 *
 * Return: string to stdout
 */

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}


/**
 * _strcmp - compare strings
 *
 * @str1: arg char
 * @str2: arg char
 *
 * Return: string to stdout
 */


int _strcmp(char *str1, char *str2)
{

	int index;

	for (index = 0; str1[index] != '\0' || str2[index] != '\0'; index++)
	{
		if (str1[index] != str2[index])
		{
			return (str1[index] - str2[index]);
		}
	}
		return (0);
}

/**
 * _strdup - copy of the string given as a parameter.
 *
 * @str: unsigned int
 *
 * Return: char pointer
 */

char *_strdup(const char *str)
{
	unsigned int counter1, counter2;
	char *strCopy;

	counter1 = 0;
	counter2 = 0;

	if (str == NULL)
	{
		return (0);
	}

	while (str[counter1] != '\0')
	{
		counter1++;
	}

	strCopy = malloc(sizeof(char) * (counter1 + 1));
	if (strCopy == NULL)
	{
		return (NULL);
	}

	while (counter2 < counter1)
	{
		strCopy[counter2] = str[counter2];
		counter2++;
	}

	strCopy[counter2] = '\0';

	return (strCopy);
}
