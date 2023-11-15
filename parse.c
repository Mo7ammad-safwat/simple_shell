#include "shell.h"


/**
 * parse_line - Uses strtok to put args in array
 *
 * @line: char pointer
 *
 * Return: Double char pointer
 */

char **parse_line(char *line)
{
	int buffer_size = BUFFERSIZE;
	int location = 0;
	char **tokens = NULL;
	char *token = NULL;

	tokens = malloc(sizeof(char *) * buffer_size);
	if (!tokens)
	{
		perror("hsh");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, DELIMINATOR);

	while (token != NULL)
	{
		tokens[location] = token;
		token = strtok(NULL, DELIMINATOR);
		location++;
	}
		if (location >= buffer_size)
		{
			buffer_size += BUFFERSIZE;
			tokens = _realloc(tokens, BUFFERSIZE,
					  buffer_size * sizeof(char *));

			if (!tokens)
			{
				{
					perror("hsh: allocation error\n");
					exit(EXIT_FAILURE);
				}
			}
			token = strtok(NULL, DELIMINATOR);
		}
	tokens[location] = NULL;
	return (tokens);
}
