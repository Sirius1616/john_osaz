#include "shell.h"

/**
 * list_len - determines length of linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @heads: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *heads)
{
	list_t *node = heads;
	size_t x = list_len(heads), y;
	char **strrs;
	char *strr;

	if (!heads || !x)
		return (NULL);
	strrs = malloc(sizeof(char *) * (x + 1));
	if (!strrs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		strr = malloc(_strlen(node->str) + 1);
		if (!strr)
		{
			for (y = 0; y < x; y++)
				free(strrs[y]);
			free(strrs);
			return (NULL);
		}

		strr = _strcpy(strr, node->str);
		strrs[x] = strr;
	}
	strrs[x] = NULL;
	return (strrs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		_puts(convert_number(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nodes: pointer to list head
 * @prefixes: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *nodes, char *prefixes, char ch)
{
	char *pt = NULL;

	while (nodes)
	{
		pt = starts_with(nodes->str, prefixes);
		if (pt && ((ch == -1) || (*pt == ch)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @heads: pointer to list head
 * @nodes: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *heads, list_t *nodes)
{
	size_t x = 0;

	while (heads)
	{
		if (heads == nodes)
			return (x);
		heads = heads->next;
		x++;
	}
	return (-1);
}
