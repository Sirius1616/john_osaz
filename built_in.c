#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Struct that contains potential arguments. Used to maintain a
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _erratoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_cd - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_cd(info_t *info)
{
	char *str, buff[1024], *dir;
	int c_dir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			c_dir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			c_dir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		c_dir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		c_dir_ret = chdir(info->argv[1]);
	if (c_dir_ret == -1)
	{
		print_error(info, "can't cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * help_cd - helper function
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int help_cd(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function yet to be implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
