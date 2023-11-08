#include "shell.h"

/**
 * get_history_file - get a history file
 * @inf: parameter
 *
 * Return: allocated string containg history file
 */
char *get_history_file(inf_t *inf)
{
	char *buf, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file or appends to a file
 * @info: the parameter
 *
 * Return: return 1
 */
int write_history(inf_t *inf)
{
	ssize_s fd;
	char *filename = get_history_file(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		e_putsfd(node->str, fd);
		e_putfd('\n', fd);
	}
	e_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read a history
 * @inf: the parameter
 *
 * Return: return 1
 */
int read_history(inf_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_s fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(inf, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(inf, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (info->histcount);
}

/**
 * build_history_list - adding entry to a history linked list
 * @info: Structure containing arguments.
 * @buf: buffer
 * @linecount: the history linecount
 *
 * Return: return 0
 */
int build_history_list(inf_t *inf, char *buf, int linecount)
{
	lis_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buf, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renumber_history - re numbers the history linked list
 * @info: Structure containing arguments
 *
 * Return: return 1
 */
int renumber_history(inf_t *inf)
{
	lis_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
