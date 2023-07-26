#include "shell.h"

/**
 * _myhistory - Display history list,
 * showing each command on a
 * separate line with line numbers starting from 0.
 * @info: Structure that may containing arguments. Maintains
 *     a consistent function prototype.
 *  Return: Always returns 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets an alias to a given string.
 * @info: Pointer to the Parameter struct.
 * @str: The string representing the alias.
 *
 * Return: 0 on success, 1 on error.
 */

int unset_alias(info_t *info, char *str)
{
	char *ptr, c;
	int retur_value;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = '0';
	retur_value = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (retur_value);
}

/**
 * set_alias - Assigns an alias to a string
 * @info: Pointer to the parameter struct
 * @str:  The string representing the alias.
 *
 * Return: 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)

		return (1);
	if (!*++ptr)

		return (unset_alias(info, str));
			unset_alias(info, str);

	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays an alias string.
 * @node: The node representing the alias.
 *
 * Return: 0 on success, 1 on error.
 */

int print_alias(list_t *node)
{
	char *ptr = NULL, *x = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (x = node->str; x < ptr; x++)
			_putchar(*x);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * _myalias - Emulates the behavior of the
 * alias builtin command (man alias).
 * @info: Structure that contains potential arguments
 * to maintain a consistent function prototype.
 *
 * Return: Always 0.
 */

int _myalias(info_t *info)
{
	int j = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
	{
		print_alias(node);
		node = node->next;
	}

		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		ptr = _strchr(info->argv[j], '=');
		if (ptr)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
