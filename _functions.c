#include "all.h"

/**
 * print_char - Print a character to the standard output.
 * @c: The character to be printed.
 *
 * Return: Number of characters printed.
 */
int print_char(char c)
{
	return (write(2, &c, 1));
}

/**
 * print_number - Print an integer to the standard output.
 * @n: The integer to be printed.
 */
void print_number(int n)
{
	unsigned int n1;

	if (n < 0)
	{
		n1 = -n;
		print_char('-');
	}
	else
		n1 = n;

	if (n1 / 10)
		print_number(n1 / 10);

	print_char((n1 % 10) + '0');
}

/**
 * print_string - Print a string to the standard output.
 * @s: The string to be printed.
 *
 * Return: Number of characters printed.
 */
int print_string(char *s)
{
	return (write(2, s, _strlen(s)));
}

/**
 * num_len - Calculate the number of digits in an integer.
 * @n: The integer to be measured.
 *
 * Return: Number of digits.
 */
int num_len(int n)
{
	int len = 1;

	print_number(n);

	if (n < 0)
		len++;

	while (n /= 10)
		len++;

	return (len);
}

/**
 * specifier - Print a formatted string based on the specifier character.
 * @c: The specifier character.
 * @args: Variable argument list.
 *
 * Return: Number of characters printed.
 */
int specifier(char c, va_list args)
{
	int len = 0;
	char *str;

	if (c == 'c')
		len += print_char(va_arg(args, int));
	else if (c == 's')
	{
		str = va_arg(args, char *);
		len += print_string(str);
	}
	else if (c == 'i' || c == 'd')
		len += num_len(va_arg(args, int));
	else if (c == '%')
		len += print_char('%');
	else
	{
		len += print_char('%');
		len += print_char(c);
	}

	return (len);
}
