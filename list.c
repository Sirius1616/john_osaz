#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @heads: address of pointer to head node
 * @strr: str field of node
 * @nums: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **heads, const char *strr, int nums) {
    if (!heads)
        return NULL;

    list_t *nw_head = (list_t *)malloc(sizeof(list_t));
    if (!nw_head)
        return NULL;

    nw_head->num = nums;
    nw_head->str = NULL;

    if (strr) {
        nw_head->str = (char *)malloc(strlen(strr) + 1);
        if (!nw_head->str) {
            free(nw_head);
            return NULL;
        }
        strcpy(nw_head->str, strr);
    }

    nw_head->next = *heads;
    *heads = nw_head;

    return nw_head;
}

/**
 * add_node_end - adds a node to the end of the list
 * @heads: address of pointer to head node
 * @strr: str field of node
 * @nums: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **heads, const char *strr, int nums) {
    if (!heads)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->num = nums;
    new_node->str = NULL;

    if (strr) {
        new_node->str = strdup(strr);
        if (!new_node->str) {
            free(new_node);
            return NULL;
        }
    }

    new_node->next = NULL;

    if (*heads) {
        list_t *node = *heads;
        for (; node->next; node = node->next)
            ;
        node->next = new_node;
    } else {
        *heads = new_node;
    }

    return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *hd) {
    size_t count = 0;

    for (; hd; hd = hd->next) {
        if (hd->str) {
            _puts(hd->str);
        } else {
            _puts("(nil)");
        }
        _puts("\n");
        count++;
    }

    return count;
}

/**
 * delete_node_at_index - deletes node at given index
 * @heads: address of pointer to first node
 * @_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **heads, unsigned int _index) {
    if (!heads || !_index)
        return 0;

    list_t *current = *heads;
    list_t *previous = NULL;

    for (unsigned int i = 0; current; i++, previous = current, current = current->next) {
        if (i == _index) {
            if (previous) {
                previous->next = current->next;
            } else {
                *heads = current->next;
            }
            free(current->str);
            free(current);
            return 1;
        }
    }

    return 0;
}

/**
 * free_list - frees all nodes of a list
 * @heads_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **heads_ptr) 
{
    if (!heads_ptr || !*heads_ptr)
        return;

    list_t *current = *heads_ptr;
    while (current) {
        list_t *next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }

    *heads_ptr = NULL;
}
