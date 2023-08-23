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
	int x;

    if (_dest == _src || _src == 0)
        return _dest;

    for (x = 0; _src[x]; x++)
    {
        _dest[x] = _src[x];
    }
    
    _dest[x] = 0;
    return _dest;
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
        return NULL;

    for (; *strr; strr++)
        lengths++;

    rt = malloc(sizeof(char) * (lengths + 1));
    if (!rt)
        return NULL;

    lengths++;
    while (lengths--)
    {
        lengths--;
        rt[lengths] = *strr--;
    }

    return rt;
}


/**
 *_puts - prints an input string
 *@strr: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *strr)
{
    if (!strr)
        return;

    for (int x = 0; strr[x] != '\0'; x++)
    {
        _putchar(strr[x]);
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
        write(1, buf, x);  // Write the contents of the buffer to standard output
        x = 0;  // Reset the buffer index
    }

    if (ch != BUF_FLUSH)
        buf[x++] = ch;  // Add the character to the buffer

    return 1;  // Return 1 to indicate success
}
