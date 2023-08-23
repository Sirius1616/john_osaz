#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Struct containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

char **get_environ(info_t *info)
{
    if (info->environ == NULL || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}


/**
 * _unsetenv - Remove an environment variable
 * @info: Struct containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */

int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;

    if (!node || !var)
        return 0;

    size_t j;
    for (j = 0; node; node = node->next, j++)
    {
        char *t = starts_with(node->str, var);
        if (t && *t == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), j);
            j = 0;
            node = info->env;
        }
    }

    return info->env_changed;
}


/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */


int _setenv(info_t *info, char *var, char *val)
{
    char *buff = NULL;
    list_t *node;
    char *t;

    if (!var || !val)
        return 0;

    buff = malloc(_strlen(var) + _strlen(val) + 2);
    if (!buff)
        return 1;

    _strcpy(buff, var);
    _strcat(buff, "=");
    _strcat(buff, val);

    for (node = info->env; node; node = node->next)
    {
        t = starts_with(node->str, var);
        if (t && *t == '=')
        {
            free(node->str);
            node->str = buff;
            info->env_changed = 1;
            return 0;
        }
    }

    add_node_end(&(info->env), buff, 0);
    free(buff);
    info->env_changed = 1;
    return 0;
}
