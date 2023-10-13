#include "all.h"
 
/**
 * _strtok - Splits the string into tokens.
 * @str: String to be divided.
 * @delim: Delimiter to split the string by.
 * Return: Token.
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
return token;
}
last++;
}

last = NULL;
return token;
}

/**
 * _strdup - Returns a pointer to space containing a copy of the given string.
 * @args: Parameter of type para p1.
 * @str: String given.
 * Return: A pointer to a duplicate string.
 */
char *_strdup(para *args, char *str)
{
if (!str)
{
return NULL;
}

int len = _strlen(str);
char *copy = _malloc(args, len + 1);

for (int i = 0; i <= len; i++)
{
copy[i] = str[i];
}

return copy;
}

/**
 * _strncmp - Compares the first n bytes of str1 and str2.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 * @n: The number of bytes to be compared.
 * Return: 0 if the strings are equal.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
while (n-- && (*str1 != '\0' || *str2 != '\0'))
{
if (*str1 != *str2)
{
return *str1 - *str2;
}
str1++;
str2++;
}

return 0;
}

/**
 * _strchr - Locates a character in a string.
 * @str: String value.
 * @c: Character to be located.
 * Return: A pointer to the first occurrence of c, or null if not found.
 */
char *_strchr(char *str, char c)
{
int i = 0;

while (i < _strlen(str))
{
if (str[i] == c)
{
return str + i;
}
i++;
}

return NULL;
}

/**
 * _strncat - Concatenates one string to another.
 * @dest: The string to be added.
 * @src: The string to be added.
 * @n: Number of bytes from src.
 * Return: The resulting concatenated string.
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
return dest;
}
