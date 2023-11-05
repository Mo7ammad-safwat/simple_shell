#include "shell.h"

/**
 *e_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: return 0
 */
void e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		e_putchar(str[i]);
		i++;
	}
}

/**
 * e_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: return 1
 */
int e_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * e_putfd - writes the character c
 * @c: The character printed
 * @fd: The description to write
 *
 * Return: return 1.
 */
int e_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input
 * @str: the string printed
 * @fd: the description to write
 *
 * Return: the number of chars
 */
int e_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += e_putfd(*str++, fd);
	}
	return (i);
}
