#include "shell.h"
/**
 * main - the main
 * @arc: length argument
 * @arv: arv argument
 * @envp: envp arguments
 * Return: 0
 */
int main(int arc, char **arv, char **envp)
{
	bool interactive = (arc == 1 && isatty(STDIN_FILENO));

	prompt(arv, envp, interactive);
	return (0);
}
