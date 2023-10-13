#include "all.h"

#define D(i) (*d)[i]

/**
 * input - Check if a new line in the shell starts with an arrow.
 * @args: Parameters of type para p1.
 * @arrow: 1 if stdin.
 * @semi: 0 or 1.
 * Return: 0, 1.
 */
int input(para *args, int arrow, int *semi)
{
ssize_t read;

read = _getline(args);
if (read == -1) {
if (isatty(STDIN_FILENO) && arrow && !args->file)
write(1, "\n", 1);
close(args->file);
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
if (*semi)
args->count--;
if (args->line[read - 1] == '\n') {
args->line[read - 1] = '\0';
}
if (args->line[read - 1] == ';') {
args->line[read - 1] = '\0';
*semi = 1;
return (0);
}
*semi = 0;
return (1);
}

/**
 * handle_input - Check if the line contains $ or # and act accordingly.
 * @args: Parameter of type para p1.
 * Return: 1 if the string is empty.
 */
int handle_input(para *args) {
char *buffer, *dollar, *start, *hash = _strchr(args->line, '#');
int buffer_size = 10240;

if (hash && ((hash != args->line && *(hash - 1) == ' ') || hash == args->line))
*hash = '\0';
buffer = _malloc(args, buffer_size);
dollar = _strchr(args->line, '$');
start = args->line;
buffer[0] = '\0';
while (dollar) {
buffer = handle_realloc(args, buffer, &buffer_size,
1024, _strlen(buffer) + dollar - start);
_strncat(buffer, start, dollar - start);
handle_dollar(buffer, &dollar, args);
start = dollar;
dollar = _strchr(start, '$');
}
buffer = handle_realloc(args, buffer, &buffer_size,
128, _strlen(buffer) + _strlen(start));
_strcat(buffer, start);
space(&buffer, args);
handle_dots(&buffer, args);
free(args->line);
args->line = buffer;
return (buffer[0] == '\0');
}

/**
 * _getline - Read an entire line from the stream.
 * @args: Parameter of type para p1.
 * Return: Number of chars read from the stream.
 */
ssize_t _getline(para *args) {
size_t i = 0;
ssize_t read_line;
char *buffer;
int buffer_size = 10240;

if (&(args->line) == NULL)
return (-1);
buffer = _malloc(args, buffer_size + 1);
if (args->line) {
free(args->line);
args->line = NULL;
}
while ((read_line = read(args->file, buffer + i, 1)) > 0) {
i++;
buffer = handle_realloc(args, buffer, &buffer_size, 2048, i);
if (buffer[i - 1] == '\n' || buffer[i - 1] == ';')
break;
}
if (read_line < 0 || (!read_line && !i)) {
free(buffer);
return (-1);
}
if (read_line != 8)
buffer[i] = '\0';
args->line = buffer;
return (i);
}

/**
 * handle_dollar - Handle input containing $ sign.
 * @buffer: Input containing $.
 * @d: Input starting from $ sign.
 * @args: Parameter of type para p3.
 */
void handle_dollar(char *buffer, char **d, para *args) {
char num[10], *env;
int i = 0;

(*d)++;
if (D(0) == '$' || D(0) == '?') {
if (D(0) == '$')
tostring(num, args->pid);
else
tostring(num, args->status);
_strcat(buffer, num);
(*d)++;
} else {
while (D(i) && D(i) != ' ' && D(i) != '#' && D(i) != '$' && D(i) != '/')
i++;
if (!i)
_strcat(buffer, "$");
else {
env = _get_env(args->envp, *d, i);
if (env)
_strcat(buffer, env);
*d += i;
}
}
}

/**
 * space - Handle extra spaces in the input.
 * @line: Input.
 * @args: Parameter of type para p2.
 */
void space(char **line, para *args) {
int i = 0, j = 0;
char *buffer = malloc(_strlen(*line) + 1);

if (buffer == NULL) {
free(*line);
free_exit(args);
}
while ((*line)[i] && (*line)[i] == ' ')
i++;
while ((*line)[i]) {
if ((*line)[i] == ' ') {
buffer[j] = ' ';
j++;
while ((*line)[i] == ' ')
i++;
} else {
buffer[j] = (*line)[i];
i++;
j++;
}
}
if (j && buffer[j - 1] == ' ')
j--;
buffer[j] = '\0';
free(*line);
*line = buffer;
}

