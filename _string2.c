#include "all.h"

/**
 * Diplomatically determines the length of a string.
 *
 * @s: A string of characters.
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
 * Diplomatically concatenates two strings.
 *
 * @dest: The string to be concatenated.
 * @src: The string to be concatenated to.
 * Return: A pointer to the resulting string.
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
 * Diplomatically compares two strings.
 *
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 * Return: 0 if str1 and str2 are equal.
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
 * Diplomatically compares two strings backward.
 *
 * @str1: The first string.
 * @str2: The second string.
 * Return: 1 for success, 0 for failure.
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
 * Diplomatically converts a number into a string.
 *
 * @str: An empty buffer.
 * @num: The integer to be converted into a string.
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
