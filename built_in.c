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
    if (info->argv[1])
    {
        int exit_code = atoi(info->argv[1]);

        if (exit_code == 0 && info->argv[1][0] != '0')
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1; // Return 1 to indicate an error
        }

        info->err_num = exit_code;
        return -2; // Return -2
    }

    info->err_num = -1;
    return -2; // Return -2
}


/**
 * change_cd - changes the current directory
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int change_cd(info_t *info)
{
    char buff[1024], *dir;
    int c_dir_ret = 0;

    char *current_dir = getcwd(buff, 1024);

    if (!current_dir)
    {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }
    else if (!info->argv[1])
    {
        dir = get_env(info, "HOME=");
        if (!dir)
        {
            dir = get_env(info, "PWD=");
        }
        c_dir_ret = chdir(dir ? dir : "/");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        char *old_pwd = get_env(info, "OLDPWD=");
        if (!old_pwd)
        {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(old_pwd);
        _putchar('\n');
        c_dir_ret = chdir(old_pwd ? old_pwd : "/");
    }
    else
    {
        c_dir_ret = chdir(info->argv[1]);
    }

    if (c_dir_ret == -1)
    {
        print_error(info, "can't cd into ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", current_dir);
        char *new_pwd = getcwd(buff, 1024);
        _setenv(info, "PWD", new_pwd);
    }

    return 0;
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
    _puts("Usage: cd [directory]\n");
    _puts("Change the current working directory.\n\n");
    _puts("Options:\n");
    _puts("  directory     The directory to change to.\n");
    
   
    if (*arg_arr)
    {
        _puts("Argument passed: ");
        _puts(*arg_arr);
        _putchar('\n');
    }

    return 0;
}
