#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing arguments
 *
 * Return: Always 0
 */
int myenv(info *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * getenv - gets the value of variable
 * @info: Structure containing arguments
 * @name: env name
 *
 * Return: return 1
 */
char *getenv(inf_t *inf, const char *name)
{
	lis_t *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - Initialize a new variable
 * @info: Structure containing arguments
 *
 *  Return: Always 0
 */
int mysetenv(inf_t *inf)
{
	if (inf->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv - Remove variable
 * @info: Structure containing arguments
 *
 *  Return: Always 0
 */
int myunsetenv(inf_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing arguments
 *
 * Return: Always 0
 */
int populateenv_list(inf_t *inf)
{
	lis_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
