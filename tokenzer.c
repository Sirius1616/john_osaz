#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @strr: the input string
 * @dc: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *strr, char *dc) {
    int x, y, z, m, numword = 0;
    char **st;

    if (strr == NULL || strr[0] == 0)
        return NULL;
    if (!dc)
        dc = " ";
	
	x = 0;

    while ( strr[x] != '\0')
    {
        if (!is_delimiter(strr[x], dc) && (is_delimiter(strr[x + 1], dc) || !strr[x + 1]))
            numword++;
	x++;
	}
    if (numword == 0)
        return NULL;

    st = malloc((1 + numword) * sizeof(char *));
    if (!st)
        return NULL;

    x = 0;
    y = 0;
    while (y < numword) {
        while (is_delimiter(strr[x], dc))
            x++;
        z = 0;
        while (!is_delimiter(strr[x + z], dc) && strr[x + z])
            z++;
        st[y] = malloc((z + 1) * sizeof(char));
        if (!st[y]) {
            for (z = 0; z < y; z++)
                free(st[z]);
            free(st);
            return NULL;
        }
        m = 0;
        while (m < z) {
            st[y][m] = strr[x++];
            m++;
        }
        st[y][m] = 0;
        y++;
    }
    st[y] = NULL;
    return st;
}



/**
 * **strtow2 - splits a string into words
 * @strr: the input string
 * @dc: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */


char **strtow2(char *strr, char dc)
{
	int x = 0, y = 0, z, m, numword = 0;
	char **st;

	if (strr == NULL || strr[0] == 0)
		return NULL;

	while (strr[x] != '\0') {
		if ((strr[x] != dc && strr[x + 1] == dc) ||
			(strr[x] != dc && !strr[x + 1]) || strr[x + 1] == dc)
			numword++;
		x++;
	}

	if (numword == 0)
		return NULL;

	st = malloc((1 + numword) * sizeof(char *));
	if (!st)
		return NULL;

	x = 0;
	y = 0;
	while (y < numword)
	{
		while (strr[x] == dc)
			x++;

		z = 0;
		while (strr[x + z] != dc && strr[x + z] && strr[x + z] != dc)
			z++;

		st[y] = malloc((z + 1) * sizeof(char));
		if (!st[y])
		{
			for (z = 0; z < y; z++)
				free(st[z]);
			free(st);
			return NULL;
		}

		m = 0;
		while (m < z) {
			st[y][m] = strr[x++];
			m++;
		}

		st[y][m] = 0;
		y++;
	}
	st[y] = NULL;
	return st;
}
