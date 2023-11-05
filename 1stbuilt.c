#include "shell.h"

/**
 * _myexit - exits
 * @info: Structure containing arguments
 *
 *  Return: exit
 */
int my_exit(inf_t *inf)
{
	int exit_check;

	if (inf->argv[1])
	{
		exit_check = _erratoi(inf->argv[1]);
		if (exit_check == -1)
		{
			inf->status = 2;
			printError(inf, "Illegal number: ");
			e_puts(info->argv[1]);
			e_putchar('\n');
			return (1);
		}
		inf->err_number = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_number = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int mycd(inf_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_result;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts(">>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = getenv(info, "HOME=");
		if (!dir)
			chdir_result = /* what should this be? */
				chdir((dir = getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_result = /*what should this be? */
			chdir((dir = getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(inf->argv[1]);
	if (chdir_result == -1)
	{
		print_error(inf, "can't cd to ");
		e_puts(inf->argv[1]),e_putchar('\n');
	}
	else
	{
		setenv(inf, "OLDPWD", getenv(info, "PWD="));
		setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory
 * @info: Structure containing  arguments
 *
 *  Return: 0
 */
int _myhelp(inf_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
