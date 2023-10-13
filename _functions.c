#include "all.h"

/**
 * print_char - Print a character.
 *
 * This function prints a single character.
 *
 * @c: The character to be printed.
 * Return: The length.
 */
int print_char(char c)
{
return (write(2, &c, 1));
}

/**
 * print_number - Print a number.
 *
 * This function prints an integer number.
 *
 * @n: The number to be printed.
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
 * print_string - Print a string.
 *
 * This function prints a string.
 *
 * @s: The string to be printed.
 * Return: The length.
 */
int print_string(char *s)
{
return (write(2, s, _strlen(s)));
}

/**
 * num_len - Calculate the length of a number.
 *
 * This function returns the length of an integer number.
 *
 * @n: The number.
 * Return: The length.
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
 * specifier - Handle and print arguments based on the specifier.
 *
 * This function handles and prints arguments based on the given specifier.
 *
 * @c: The specifier character.
 * @args: The variable arguments list.
 * return: The length.
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
