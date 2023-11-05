#include "shell.h"

/**
 * is_chain - test if current char is delimeter
 * @info: the parameter
 * @buf: the char
 * @p: address of current position
 *
 * Return: return 1
 */
int is_chain(inf_t *inf, char *buf, size_s *p)
{
	size_s j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks if we should continue
 * @info: the parameter
 * @buf: the buffer
 * @p: address of current position
 * @i: start position
 * @len: length
 *
 * Return: Null
 */
void check_chain(inf_t *inf, char *buf, size_s *p, size_s i, size_s len)
{
	size_s j = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases
 * @info: the parameter
 *
 * Return: return 1
 */
int replace_alias(inf_t *inf)
{
	int i;
	lis_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars
 * @info: the parameter
 *
 * Return: return 1
 */
int replace_vars(inf_t *inf)
{
	int i = 0;
	lis_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replace string
 * @old: address string old
 * @new: new string
 *
 * Return: return 1
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
