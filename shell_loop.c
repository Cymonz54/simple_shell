#include "shell.h"

/**
 * hsh - Executes the main shell loop.
 * @info: The structure containing input parameters and return values.
 * @av: The argument vector passed from the main() function.
 * Return: 0 on successful execution, 1 on error,
 * or an error code indicating the specific error.
 */

int hsh(info_t *info, char **av)

{
	ssize_t s = 0;
	int builtin_ret = 0;

	while (s != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds the builtin command.
 * @info: The structure containing input parameters and return values.
 * Return: -1 if builtin command not found,
 * 0 if builtin command executed successfully,
 * 1 if builtin command found but not successful,
 * 2 if builtin command signals exit().
 */

int find_builtin(info_t *info)

{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[j].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Finds a command in the path
 * @info: The structure containing input parameters and return values.
 *
 * Return: void
 */

void find_cmd(info_t *info)

{
	char *path = NULL;
	int n, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (n = 0, m = 0; info->arg[n]; n++)
		if (!is_delim(info->arg[n], " \t\n"))
			m++;
	if (!m)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an execution thread to run a command.
 * @info: The structure containing input parameters and return values.
 *
 * Return: void
 */

void fork_cmd(info_t *info)

{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
