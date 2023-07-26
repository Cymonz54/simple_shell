#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified number of characters.
 * @dest: The destination string to copy to.
 * @src: The source string copied from.
 * @n: The number of characters to copy.
 *
 * Return: Pointer to the destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates two strings up to a specified number of bytes.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of bytes to concatenate.
 *
 * Return: Pointer to the destination string.
 */

char *_strncat(char *dest, char *src, int n)
{
	int dest_len = strlen(dest);
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * *_strchr - Locates the first occurrence of a
 * characterin a string
 * @s: The string to be searched
 * @c: The character to be look for
 *
 * Return: A pointer to the memory area where
 * the character is found
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	if (c == '\0')
		return (s);

	return (NULL);
}
