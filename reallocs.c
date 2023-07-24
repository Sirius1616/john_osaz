#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@sr: the pointer to the memory area
 *@br: the byte to fill *s with
 *@m: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *sr, char br, unsigned int m)
{
	unsigned int x;

	for (x = 0; x < m; x++)
	sr[x] = br;
	return (sr);
}

/**
 * ffree - frees a string of strings
 * @ppl: string of strings
 */
void ffree(char **ppl)
{
	char **aa = ppl;

	if (!ppl)
		return;
	while (*ppl)
		free(*ppl++);
	free(aa);
}

/**
 * _realloc - reallocates a block of memory
 * @ptrr: pointer to previous malloc'ated block
 * @old_sizee: byte size of previous block
 * @new_sizee: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptrr, unsigned int old_sizee, unsigned int new_sizee)
{
	char *pp;

	if (!ptrr)
		return (malloc(new_sizee));
	if (!new_sizee)
		return (free(ptrr), NULL);
	if (new_sizee == old_sizee)
		return (ptrr);

	pp = malloc(new_sizee);
	if (!pp)
		return (NULL);

	old_sizee = old_sizee < new_sizee ? old_sizee : new_sizee;
	while (old_sizee--)
		pp[old_sizee] = ((char *)ptrr)[old_sizee];
	free(ptrr);
	return (pp);
}
