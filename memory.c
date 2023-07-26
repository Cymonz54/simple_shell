#include "shell.h"

/**
 * bfree - Frees the pointer and NULLs the address.
 * @ptr: Pointer to the pointer that it frees.
 *
 * Return: 1 if the block was successfully freed,
 *         otherwise 0.
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
