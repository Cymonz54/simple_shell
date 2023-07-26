#include "shell.h"

/**
 * _strlen - It Returns the length of a string.
 * @s: The string to calculate the length of
 *
 * Return: The length of string as an integer
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;

	return (a);
}

/**
 * _strcmp - Compare two string lexiographicallly
 * @s1: The first string to compare
 * @s2: The second string to compare
 *
 * Return: An integer less than, equal to, or greater than zero if s1
 * is lexicographically less than, equal to or grEATER than s2.
 */

int _strcmp(char *s1, char *s2)

{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specific substring
 * @haystack: The String to search for.
 * @needle: The substring to be found.
 *
 * Return: Address of the next char of haystack if needle stars with
 * haystack, or NULL if not found.
 */

char *starts_with(const char *haystack, const char *needle)

{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (ret);
}
