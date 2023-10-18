#include "shell.h"
/**
 * trim - delete whitespace
 * @cmd: the comand
 * Return: 1
 */
char *trim(char *cmd)
{
	char *cpcmd;
	int i = 0, len;

	while (cmd[i] == ' ')
		i++;
	len = _strlen(cmd) - i + 1;
	cpcmd = malloc(len + 1);
	if (!cpcmd)
	{
		perror("Allocation Failed\n");
		return (NULL);
	}
	_strncpy(cpcmd, cmd + i, len);
	cpcmd[len] = '\0';
	_strcpy(cmd, cpcmd);
	free(cpcmd);
	return (cmd);
}
