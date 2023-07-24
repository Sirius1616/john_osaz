#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pp: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *buff, size_t *pp)
{
	size_t x = *pp;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[x] == ';') /* found end of this command */
	{
		buff[x] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pp = x;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pp: address of current position in buf
 * @x: starting position in buf
 * @_len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buff, size_t *pp, size_t x, size_t _len)
{
	size_t y = *pp;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[x] = 0;
			y = _len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[x] = 0;
			y = _len;
		}
	}

	*pp = y;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int x;
	list_t *nodes;
	char *pp;

	for (x = 0; x < 10; x++)
	{
		nodes = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!nodes)
			return (0);
		free(inf->argv[0]);
		pp = _strchr(nodes->str, '=');
		if (!pp)
			return (0);
		pp = _strdup(pp + 1);
		if (!pp)
			return (0);
		inf->argv[0] = pp;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int x = 0;
	list_t *nodes;

	for (x = 0; inf->argv[x]; x++)
	{
		if (inf->argv[x][0] != '$' || !inf->argv[x][1])
			continue;

		if (!_strcmp(inf->argv[x], "$?"))
		{
			replace_string(&(inf->argv[x]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[x], "$$"))
		{
			replace_string(&(inf->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nodes = node_starts_with(inf->env, &inf->argv[x][1], '=');
		if (nodes)
		{
			replace_string(&(inf->argv[x]),
				_strdup(_strchr(nodes->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @_old: address of old string
 * @_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **_old, char *_new)
{
	free(*_old);
	*_old = _new;
	return (1);
}
