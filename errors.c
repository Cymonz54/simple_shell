#include "shell.h"

/**
 * _eputs - Prints a string to the standard error output.
 * @str: String to be printed out.
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Writes a character to the standard error stream (stderr).
 * @c: character to be printed.
 *
 * Return: On success 1, On error, -1 is returned
 * and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;

	return (1);
}

/**
 * _putfd - Writes a character to the specified file descriptor.
 * @c: The character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success 1, On error, -1 is returned
 * and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _putsfd - Writes a string to the specified file descriptor.
 * @str: The string to be written
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */

int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
