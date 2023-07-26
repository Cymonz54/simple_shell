#include "shell.h"

/**
 * clear_info - Initializes the info_t struct
 * @info: Pointer to the info_t struct
 *
 * This function initializes the specified members of the
 * info_t struct to their default values or NULL.
 */

void clear_info(info_t *info)

{
	if (!info)
		return;

	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes the info_t struct
 * @info: Pointer to the info_t struct
 * @av: Argument vector
 * Description: This function initializes the fields of the info_t struct
 * with the provided values.
 *
 * Return: None
 */

void set_info(info_t *info, char **av)

{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees fields of the info_t struct
 * @info: pointer to the info_t struct
 * @all: flag indicating whether to free all fields
 * This function frees the specified fields of the info_t struct.
 * If the 'all' parameter is set to true, it frees all fields.
 * Otherwise, it only sets the fields to NULL and resets the counter.
 */

void free_info(info_t *info, int all)

{
	if (info->argv)
	{
		ffree(info->argv);
		info->argv = NULL;
	}
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
		{
			free(info->arg);
			info->arg = NULL;
		}
		if (info->env)
		{
			free_list(&(info->env));
			info->env = NULL;
		}
		if (info->history)
		{
			free_list(&(info->history));
			info->history = NULL;
		}
		if (info->alias)
		{
			free_list(&(info->alias));
			info->alias = NULL;
		}
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		info->cmd_buf = NULL;

		if (info->readfd > 2)
		{
			close(info->readfd);
		}
		_putchar(BUF_FLUSH);
	}
}
