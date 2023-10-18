#include "shell.h"

/**
 * bfree - frees the pointer
 * @ptr: address of the pointer
 *
 * Return: return 1
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
