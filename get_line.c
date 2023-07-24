#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_pt = 0;

	if (!*len) /* if buffer is null, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_pt, stdin);
#else
		r = get_line(info, buf, &len_pt);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line excluding the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t q = 0;
	char **buf_pt = &(info->arg), *pt;

	_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
	if (q == -1) /* EOF is reached */
		return (-1);
	if (len)
	{
		j = i; /* initialize new iterator to current buf position */
		pt = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_pt = pt; /* pass back pointer to current command position */
		return (_strlen(pt)); /* return length of current command */
	}

	*buf_pt = buf; /* if not a chain, pass back buffer from _getline() */
	return (q); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: q
 */
ssize_t read_buf(info_t *info, char *buf, size_t *j)
{
	ssize_t q = 0;

	if (*j)
		return (0);
	q = read(info->readfd, buf, READ_BUF_SIZE);
	if (q >= 0)
		*j = q;
	return (q);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @length: length of preallocated pointer buffer
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t z;
	ssize_t q = 0, s = 0;
	char *pt = NULL, *new_pt = NULL, *c;

	pt = *ptr;
	if (pt && length)
		s = *length;
	if (j == len)
		j = len = 0;

	q = read_buf(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	z = c ? 1 + (unsigned int)(c - buf) : len;
	new_pt = _realloc(pt, s, s ? s + z : z + 1);
	if (!new_pt) /* if malloc fails */
		return (pt ? free(pt), -1 : -1);

	if (s)
		_strncat(new_pt, buf + j, z - j);
	else
		_strncpy(new_pt, buf + j, z - j + 1);

	s += z - j;
	j = z;
	pt = new_pt;

	if (length)
		*length = s;
	*ptr = pt;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sign_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sign_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
