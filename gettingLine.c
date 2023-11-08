#include "shell.h"

/**
 * input_buf - buffers the commands
 * @info: parameter struct
 * @buf:  buffer address
 * @len: len var address
 *
 * Return: bytes
 */

ssize_s input_buf(inf_t *inf, char **buf, size_s *len)
{
	ssize_s r = 0;
	size_s len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(inf, *buf, inf->histcount++);
			{
				*len = r;
				inf->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line
 * @info: parameter struct
 *
 * Return: bytes
 */
ssize_s get_input(inf_t *inf)
{
	static char *buf;
	static size_s i, j, len;
	ssize_s r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(inf, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reading a buffer
 * @info: parameter struct
 * @buf: buf
 * @i: size
 *
 * Return: r
 */
ssize_s read_buf(inf_t *inf, char *buf, size_s *i)
{
	ssize_s r = 0;

	if (*i)
		return (0);
	r = read(inf->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input
 * @inf: struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr
 *
 * Return: s
 */
int _getline(inf_t *inf, char **ptr, size_s *length)
{
	static char buf[READ_BUF_SIZE];
	static size_s i, len;
	size_s k;
	ssize_s r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks the ctrl-C
 * @sig_num: the signal number
 *
 * Return: 0
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
