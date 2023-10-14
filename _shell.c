#include "all.h"

/**
 * _command_ - Execute commands based on input.
 *
 * This function handles various commands like exit, cd, env, and executes programs
 * in the PATH environment variable.
 *
 * @args: The parameter structure.
 *
 * Return: The status of the command execution.
 */
int _command_(para *args)
{
	int i;
	char *path = args->path;

	if (_exit_(args) || cd(args))
		return (args->status);

	if (args->line[0] == '/')
	{
		if (access(args->line, X_OK) == 0)
		{
			if (!_env(args))
				return (_execeve(args, args->line));
			return (0);
		}
		_printf("%s: %i: %s: not found\n", args->shell_name, args->count, args->line);
	}
	else
	{
		if (!_strcmp(args->line, "env") && _env(args))
			return (0);
		for (i = 0; i < args->n_path; i++)
				{
					char buffer[500] = "";

					_strcat(buffer, path);
					_strcat(buffer, "/");
					_strcat(buffer, args->line);

					if (access(buffer, X_OK) == 0)
						return (_execeve(args, buffer));

					path += _strlen(path) + 1;
				}

		_printf("%s: %i: %s: not found\n", args->shell_name, args->count, args->line);
	}

	args->status = 127;
	return (127);
}

/**
 * _execeve - Execute a program.
 *
 * This function uses execve to execute a program.
 *
 * @args: The parameter structure.
 * @buff: The program path.
 *
 * Return: The exit status of the executed program.
 */
int _execeve(para *args, char *buff)
{
	char **arg_v, *line = args->line;
	int i;
	pid_t id = fork();

	if (!id)
	{
		if (rev_cmp(args->line, "pwd"))
		{
			arg_v = malloc(16);
			if (arg_v == NULL)
				exit(255);
			arg_v[0] = args->line;
			arg_v[1] = NULL;
		}
		else
		{
			arg_v = malloc(8 * (args->n_token + 1));
			if (arg_v == NULL)
				exit(255);
			for (i = 0; i < args->n_token; i++)
			{
				arg_v[i] = line;
				line += _strlen(line) + 1;
			}
			arg_v[i] = NULL;
		}

		execve(buff, arg_v, NULL);

		free(arg_v);
		exit(args->status);
	}

	wait(&(args->status));
	args->status = WEXITSTATUS(args->status);
	return (args->status);
}

/**
 * _exit_ - Handle exit command.
 *
 * This function handles the exit command and terminates the shell if executed.
 *
 * @args: The parameter structure.
 *
 * Return: 1 if the command was exit, otherwise 0.
 */
int _exit_(para *args)
{
	int len;

	if (!_strcmp(args->line, "exit"))
	{
		if (args->n_token > 1)
		{
			len = _strlen(args->line) + 1;
			args->status = _atoi(args->line + len);
		}

		if (args->status != -1)
		{
			if (args->line)
				free(args->line);
			if (args->path)
				free(args->path);
			if (args->pwd)
				free(*(args->pwd));
			if (args->old_pwd)
				free(args->old_pwd);
			exit(args->status);
		}

		_printf("%s: %i: exit: Illegal number: %s\n",
				args->shell_name, args->count, args->line + len);
		args->status = 2;
		return (1);
	}

	return (0);
}

/**
 * ctrl_c - Handle SIGINT signal (Ctrl+C).
 *
 * This function handles the SIGINT signal (Ctrl+C) and prints a newline followed by
 * the shell prompt.
 *
 * @signal: The signal received (SIGINT).
 */
void ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n=> ", 4);
	}
}

/**
 * main - Entry point of the shell program.
 *
 * @argc: The number of command line arguments.
 * @argv: An array of strings representing the command line arguments.
 * @envp: An array of strings representing the environment variables.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **envp)
{
	para args;
	int arrow = 1, semi = 0;

	args.line = NULL, args.path = NULL;
	args.envp = envp;
	args.pwd = NULL;
	args.old_pwd = NULL;
	args.path = _strdup(&args, _get_env(envp, "PATH", 4));
	args.pwd = get_PWD(&args);
	if (args.pwd)
		args.old_pwd = _strdup(&args, &((*args.pwd)[4]));
	args.shell_name = argv[0];
	args.count = 0;
	args.status = 0;
	args.file = 0;
	args.pid = (int)getpid();
	args.n_path = token(args.path, ":");
	if (argc > 1)
	{
		args.file = open(argv[1], O_RDONLY);
		if (args.file == -1)
		{
			_printf("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
			exit(2);
		}
	}

	while (1)
	{
		if (isatty(STDIN_FILENO) && arrow && !args.file)
			write(1, "=> ", 3);

		signal(SIGINT, ctrl_c);

		args.count++;
		arrow = input(&args, arrow, &semi);
		if (handle_input(&args))
			continue;
		args.n_token = token(args.line, " ");
		if (_command_(&args) == 255)
			free_exit(&args);
	}

	return (0);
}
