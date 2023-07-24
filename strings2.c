#include "shell.h"

/**
 * _strcpy - copies a string
 * @_dest: the destination
 * @_src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *_dest, char *_src)
{
	int x = 0;

	if (_dest == _src || _src == 0)
		return (_dest);
	while (_src[x])
	{
		_dest[x] = _src[x];
		x++;
	}
	_dest[x] = 0;
	return (_dest);
}

/**
 * _strdup - duplicates a string
 * @strr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *strr)
{
	int lengths = 0;
	char *rt;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		lengths++;
	rt = malloc(sizeof(char) * (lengths + 1));
	if (!rt)
		return (NULL);
	for (lengths++; lengths--;)
		rt[lengths] = *--strr;
	return (rt);
}

/**
 *_puts - prints an input string
 *@strr: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strr)
{
	int x = 0;

	if (!strr)
		return;
	while (strr[x] != '\0')
	{
		_putchar(strr[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}
