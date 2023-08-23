#include "shell.h"

/**
 * list_len - determines length of linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */

size_t list_len(const list_t *hd) {
    size_t count = 0;

    for (; hd; hd = hd->next) {
        count++;
    }

    return count;
}


/**
 * list_to_strings - returns an array of strings of the list->str
 * @heads: pointer to first node
 *
 * Return: array of strings
 */


char **list_to_strings(list_t *heads) {
    size_t length = 0;
    list_t *node = heads;
    
    // Calculate the length of the list
    while (node) {
        length++;
        node = node->next;
    }
    
    // Allocate memory for the string array
    char **str_array = malloc(sizeof(char *) * (length + 1));
    if (!str_array)
        return NULL;
    
    // Copy the strings into the array
    node = heads;
    for (size_t i = 0; i < length; i++) {
        str_array[i] = strdup(node->str);
        if (!str_array[i]) {
            for (size_t j = 0; j < i; j++) {
                free(str_array[j]);
            }
            free(str_array);
            return NULL;
        }
        node = node->next;
    }
    
    str_array[length] = NULL; // Mark the end of the array
    
    return str_array;
}


/**
 * print_list - prints all elements of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *hd) {
    size_t count = 0;

    for (; hd; hd = hd->next) {
        _puts(convert_number(hd->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(hd->str ? hd->str : "(nil)");
        _puts("\n");
        count++;
    }

    return count;
}


/**
 * node_starts_with - returns node whose string starts with prefix
 * @nodes: pointer to list head
 * @prefixes: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_starts_with(list_t *nodes, char *prefixes, char ch) {
    for (; nodes; nodes = nodes->next) {
        char *pt = starts_with(nodes->str, prefixes);
        if (pt && (ch == -1 || *pt == ch)) {
            return nodes;
        }
    }
    return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @heads: pointer to list head
 * @nodes: pointer to the node
 *
 * Return: index of node or -1
 */


ssize_t get_node_index(list_t *heads, list_t *nodes) {
    size_t index = 0;

    for (; heads; heads = heads->next, index++) {
        if (heads == nodes) {
            return index;
        }
    }
    
    return -1;
}
