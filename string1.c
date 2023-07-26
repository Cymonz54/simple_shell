#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination buffer.
 * @src: The source the buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;

	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: Pointer to duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * _puts - Prints a string.
 * @str:String to be printed.
 *
 * Return: None.
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;

	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - Write the character c to the stdout.
 * @c: The character to be printed.
 *
 * Return: On success, returns 1.
 * On error,return -1 and errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}

	if (c != BUF_FLUSH)
		buf[j++] = c;

	return (1);
}
