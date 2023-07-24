#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @strr: the input string
 * @dc: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *strr, char *dc)
{
	int x, y, z, m, numword = 0;
	char **st;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	if (!dc)
		dc = " ";
	for (x = 0; strr[x] != '\0'; x++)
		if (!is_delimiter(strr[x], dc) && (is_delimiter(strr[x + 1],
dc) || !strr[x + 1]))
			numword++;

	if (numword == 0)
		return (NULL);
	st = malloc((1 + numword) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < numword; y++)
	{
		while (is_delimiter(strr[x], dc))
			x++;
		z = 0;
		while (!is_delimiter(strr[x + z], dc) && strr[x + z])
			z++;
		st[y] = malloc((z + 1) * sizeof(char));
		if (!st[y])
		{
			for (z = 0; z < y; z++)
				free(st[z]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			st[y][m] = strr[x++];
		st[y][m] = 0;
	}
	st[y] = NULL;
	return (st);
}

/**
 * **strtow2 - splits a string into words
 * @strr: the input string
 * @dc: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *strr, char dc)
{
	int x, y, z, m, numword = 0;
	char **st;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	for (x = 0; strr[x] != '\0'; x++)
		if ((strr[x] != dc && strr[x + 1] == dc) ||
		    (strr[x] != dc && !strr[x + 1]) || strr[x + 1] == dc)
			numword++;
	if (numword == 0)
		return (NULL);
	st = malloc((1 + numword) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < numword; y++)
	{
		while (strr[x] == dc && strr[x] != dc)
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
			return (NULL);
		}
		for (m = 0; m < z; m++)
			st[y][m] = strr[x++];
		st[y][m] = 0;
	}
	st[y] = NULL;
	return (st);
}
