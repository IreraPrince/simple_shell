#include "shell.h"
#include <stdlib.h>

/**
 * bfree - function frees a pointer and sets address to NULL
 * @ptr: location of pointer to be freed
 *
 * Return: 1 if successful, 0 if it fails
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
