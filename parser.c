#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable.
 * @info: The parser_info structure.
 * @path: Path to the file.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */

int is_cmd(info_t *info, char *path)

{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))

		return (0);
	if (st.st_mode & S_IFREG)

		return (1);

	return (0);
}

/**
 * dup_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */

char *dup_chars(char *pathstr, int start, int stop)

{
	static char buf[1024];
	int i, k;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = '\0';

	return (buf);
}

/**
 * find_path - Finds this command in the Path string.
 * @info: The parser_info struct.
 * @pathstr: The Path string.
 * @cmd: The command to be found.
 *
 * Return: Full path of the command if found or NULL.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)

{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}

		i++;
	}

	return (NULL);
}
