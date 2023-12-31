#include "shell.h"

/**
 * get_history - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history(info_t *info)
{
	char *buff, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or adds to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info) {
    ssize_t fd;
    char *file_name = get_history(info);
    list_t *node = info->history;  // Initialize the node to the first element

    if (!file_name)
        return -1;

    fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);

    if (fd == -1)
        return -1;

    while (node) {
        _putsfd(node->str, fd);  // Assuming _putsfd writes the string to the file descriptor
        _putfd('\n', fd);        // Write a newline character
        node = node->next;       // Move to the next node
    }

    _putfd(BUF_FLUSH, fd);  // Flush the buffer to the file

    close(fd);

    return 1;
}


/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info) {
    int j, last = 0, line_count = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buff = NULL, *file_name = get_history(info);

    if (!file_name)
        return 0;

    fd = open(file_name, O_RDONLY);
    free(file_name);
    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2) {
        close(fd);
        return 0;
    }

    buff = malloc(sizeof(char) * (fsize + 1));
    if (!buff) {
        close(fd);
        return 0;
    }

    rdlen = read(fd, buff, fsize);
    buff[fsize] = 0;

    if (rdlen <= 0) {
        free(buff);
        close(fd);
        return 0;
    }

    close(fd);

    j = 0;
    while (j < fsize) {
        if (buff[j] == '\n') {
            buff[j] = 0;
            build_history(info, buff + last, line_count++);
            last = j + 1;
        }
        j++;
    }

    if (last != j)
        build_history(info, buff + last, line_count++);

    free(buff);

    info->histcount = line_count;

    for (; info->histcount >= HIST_MAX; info->histcount--) {
        delete_node_at_index(&(info->history), 0);
    }

    re_number_history(info);

    return info->histcount;
}


/**
 * build_history - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history(info_t *info, char *buff, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * re_number_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int re_number_history(info_t *info) {
    list_t *node = info->history;  // Start from the head of the linked list
    int j;

    for (j = 0; node; j++) {
        node->num = j;  // Assign the current value of 'j' to the 'num' field
        node = node->next;  // Move to the next node
    }

    info->histcount = j;  // Update the history count in the 'info' structure

    return info->histcount;  // Return the updated history count
}
