#include "shell.h"

/**
 * input_buf - Buffers chained commands for processing.
 * @info: Structure containing parameter information.
 * @buf: Address of the buffer to store the input.
 * @len: Address of the variable to store the length of the input.
 *
 * Return: The number of bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t new_len = 0;

	if (!*len) /* If there is nothing left in the buffer, fill it */
	{
		/* buf free ((void **)info -> cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &new_len, stdin);
#else
		bytes_read = _getline(info, buf, &new_len);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; /* Removes any trailing in the newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Retrieves a line of input without the newline
 * character
 * @info: Structure containing parameter information.
 *
 * Return: The number of bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command to chain the buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* End of file */
		return (-1);
	if (len) /* commands left in the chain buffer */
	{
		j = i; /* To initialize new iterator to the current buffer position */
		p = buf + i; /* Get the pointer to return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* To iterate to semic-olon or the end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* To ncrement the past nullfied ';' */
		if (i >= len) /* Have reached at end of buffer? */
		{
			i = len = 0; /* Resets the position & the length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Passes back the  pointer to current command position */
		return (_strlen(p)); /* Return the length of current command position */
	}

	*buf_p = buf; /* If not a chain, then pass back buffer from _getline() */
	return (r); /* Returns the length of buffer from _getline() */
}

/**
 * read_buf - Reads from a file descriptor into a buffer.
 * @info: The parameter & return info struct.
 * @buf: The buffer to read into.
 * @i: A pointer to the size of the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i != 0)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - Reads the next line of input from STDIN.
 * @info: The parameter & return info struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The string containing the read line.
 */

int _getline(info_t *info, char **ptr, size_t *length)

{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	size_t k;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (size_t)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)/* MALLOC FAILURE! */
	{
		if (p)
			free(p);
		return (-1);
	}
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl-C)
 * @sig_num: The signal number
 * Description: This function handles the SIGINT signal
 * (Ctrl-C) and performs the necessary actions when
 * the signal is received. It prints a newline and
 * a prompt to indicate the interruption,
 * allowing the shell to continue.
 *
 * Return: None
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
