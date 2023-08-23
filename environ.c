#include "shell.h"

/**
 * my_env - prints current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environ var name
 *
 * Return: the value
 */

char *get_env(info_t *info, const char *name) {
    list_t *node;

    for (node = info->env; node != NULL; node = node->next) {
        if (starts_with(node->str, name)) {
            return starts_with(node->str, name);  // Return the matched portion of the string
        }
    }

    return NULL;  // Return NULL if the environment variable is not found
}


/**
 * my_set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int my_set_env(info_t *info) {
    if (info->argc != 3) {
        _eputs("wrong number of arguments\n");  // Print an error message
        return 1;  // Return 1 to indicate an error
    }

    int success = _setenv(info, info->argv[1], info->argv[2]);
    return (success) ? 0 : 1;  // Return 0 if _setenv succeeded, otherwise return 1
}


/**
 * my_unset_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int my_unset_env(info_t *info) {
    int j = 1;

    if (info->argc == 1) {
        _eputs("Too few arguments.\n");  // Print an error message
        return 1;  // Return 1 to indicate an error
    }

    while (j <= info->argc) {
        _unsetenv(info, info->argv[j]);  // Unset the environment variable
        j++;
    }

    return 0;  // Return 0 to indicate success
}


/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int populate_env_list(info_t *info) {
    list_t *node = NULL;
    size_t j = 0;

    while (environ[j]) {
        add_node_end(&node, environ[j], 0);  // Add a node with environment variable to the end of the linked list
        j++;
    }

    info->env = node;  // Update the environment variable linked list in the info structure

    return 0;  // Return 0 to indicate successful population
}
