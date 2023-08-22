#include "shell.h"

/**
 * _memset - function ensures memory is filled with constnt byte
 * @s: address to memory area
 * @b: points byte to fill *s with
 * @n: number of bytes to fill
 * Return: (s) pntr to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - frees the string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **j = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(j);
}

/**
 * _realloc - reallocates memory block
 * @ptr: pntr to the previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pntr to old block memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *z;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	z = malloc(new_size);
	if (!z)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (z);
}
