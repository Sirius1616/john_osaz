#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @ave: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *inf, char **ave)
{
	ssize_t x = 0;
	int builtin_rt = 0;

	while (x != -1 && builtin_rt != -2)
	{
		clear_info(inf);
		if (interact(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(inf);
		if (x != -1)
		{
			set_info(inf, ave);
			builtin_rt = find_builtin(inf);
			if (builtin_rt == -1)
				find_cmd(inf);
		}
		else if (interact(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interact(inf) && inf->status)
		exit(inf->status);
	if (builtin_rt == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_rt);
}

/**
 * find_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(info_t *inf)
{
	int x, built_in_rt = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", help_cd},
		{"history", my_hist},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", change_cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(inf->argv[0], builtintbl[x].type) == 0)
		{
			inf->line_count++;
			built_in_rt = builtintbl[x].func(inf);
			break;
		}
	return (built_in_rt);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int x, y;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (x = 0, y = 0; inf->arg[x]; x++)
		if (!is_delimiter(inf->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interact(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pids;

	child_pids = fork();
	if (child_pids == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pids == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}
