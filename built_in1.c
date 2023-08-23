#include "shell.h"

/**
 * my_hist - displays the history list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_hist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *s)
{
    char *equal_sign, temp_char;
    int ret;

    equal_sign = strchr(s, '=');
    if (!equal_sign)
        return 1;
    
    temp_char = *equal_sign;
    *equal_sign = '\0';

    int alias_index = get_node_index(info->alias, node_starts_with(info->alias, s, -1));
    ret = delete_node_at_index(&(info->alias), alias_index);

    *equal_sign = temp_char;
    
    return ret;
}


/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
    char *equal_sign;

    equal_sign = strchr(str, '=');
    if (!equal_sign)
        return 1;

    if (!*++equal_sign)
        return unset_alias(info, str);

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */


int print_alias(list_t *node)
{
    if (node)
    {
        char *equal_sign = strchr(node->str, '=');
        if (equal_sign)
        {
            size_t alias_name_length = equal_sign - node->str;
            size_t i = 0;
            
            while (i < alias_name_length)
            {
                _putchar(node->str[i]);
                i++;
            }
            
            _puts("'");
            _puts(equal_sign + 1);
            _puts("'\n");
            
            return 0;
        }
    }
    
    return (1);
}


/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _myalias(info_t *info)
{
    int j = 1;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    while (info->argv[j])
    {
        p = _strchr(info->argv[j], '=');
        if (p)
            set_alias(info, info->argv[j]);
        else
            print_alias(node_starts_with(info->alias, info->argv[j], '='));

        j++;
    }

    return 0;
}
