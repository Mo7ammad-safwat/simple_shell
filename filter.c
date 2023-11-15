#include "shell.h"

/**
 * function_filter - Filters built-ins & sends them to appropriate function
 *
 * @commands: Double pointer from command line
 *
 * @env: Environment variable
 *
 * Return: exec_cmd function
 */

int function_filter(char **commands, char **env)
{
	int option = 0;
	char *builtin[7] = {"exit", "cd", "env", "holberton", "unsetenv",
			    "setenv", NULL};

	if (commands[0] == NULL) /* If no args at all, continue */
		return (1);
	while (builtin[option] != NULL)
	{
		if (_strcmp(builtin[option], commands[0]) == 0)
			break;
		option++;
	}
	switch (option)
	{
	case 0: /* Exit */
		if (commands[1] == NULL) /* Only exit is typed */
			call_exit(commands);
		else
			call_exit_status(commands); /* Is 2nd arg after exit */
		break;
	case 1:
		call_cd(commands); /* cd is typed */
		break;
	case 2:
		call_env(env); /* env is typed */
		break;
	case 3:
		WhoAmI();
		break;
	case 4:
		call_unsetenv(env, commands);
		break;
	case 5:
		call_setenv(env, commands);
		break;
	default:
		return (exec_cmd(commands, env)); /* No builtin found */
	}
	return (option);
}
