#include "shell.h"

/**
 * _myenv - Displays the current environment.
 * @info: Structure that contains potential arguments,
 * maintaining consistent function prototype.
 *
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Structure that contains potential arguments,
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	char *ptr;

	while (current_node)
	{
		ptr = starts_with(current_node->str, name);
		if (ptr && *ptr)
			return (ptr);
		current_node = current_node->next;
	}

	return (NULL);
}

/**
 * _mysetenv - Sets or modifies an environment variable.
 * @info: Structure that contains potential arguments.
 *
 *  Return: Always return 0.
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @info: Structure Structure that contains potential arguments.
 *
 * Return: Always return 0.
 */

int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure that contains potential arguments.
 *
 * Return: Always return 0.
 */

int populate_env_list(info_t *info)
{
	list_t *env_list = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&env_list, environ[j], 0);
	info->env = env_list;

	return (0);
}
