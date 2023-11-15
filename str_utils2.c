#include "shell.h"

/**
 * _getchar - Gets a character
 *
 * Return: Character
 */

int _getchar(void)
{
	char buffer[BUFFERSIZE];
	char *buff = buffer;
	int index = 0;

	if (index == 0)
	{
		index = read(0, buffer, 1);
	}
	if (index-- >= 0)
	{
		return (*buff++);
	}
	return (EOF);
}


/**
 * _atoi - Convert a string to an integer.
 *
 * @s: input string
 *
 * Return: integer
 */

int  _atoi(char *s)
{
	int sign, result, index;

	result = 0;
	sign = 0;

	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] == '-')
		{
			sign++;
		}
		if (s[index] > 47 && s[index] < 58)
		{
			while (s[index] > 47 && s[index] < 58)
			{
				result = result * 10 - (s[index++] - 48);
				break;
			}
		}
	}
	return (result *= sign % 2 == 0 ? -1 : 1);
}


/**
 * word_counter - Counts words
 *
 * @str: char pointer
 *
 * Return: Integer
 */


int word_counter(char *str)
{
	int count1, count2 = 0;

	for (count1 = 0; str[count1] != '\0'; count1++)
	{
		if (str[count1] != ' ' && (str[count1 + 1] == ' ' ||
					   str[count1 + 1] == '\0'))
		{
			count2++;
		}
	}
	return (count1);
}

/**
 * _strcat - Adds two strings together
 * @s1: First string to add
 * @s2: Second string to add
 * Return: Always temp
 */

char *_strcat(char *s1, char *s2)
{
	int i, j, k, size;
	char *temp;

	i = 0;
	j = 0;
	k = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;

	size = i + j + 1;
	temp = malloc(size * sizeof(char));
	if (temp == NULL)
		return (NULL);

	j = 0;

	while (k < size)
	{
		if (k < i)
		{
			temp[k] = s1[k];
		}
		else
		{
			temp[k] = s2[j];
			j++;
		}
		k++;
	}

	temp[k - 1] = '\0';
	return (temp);
}
