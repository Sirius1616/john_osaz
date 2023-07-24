#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *paths)
{
	struct stat sts;

	(void)inf;
	if (!paths || stat(paths, &sts))
		return (0);

	if (sts.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstrr: the PATH string
 * @_start: starting index
 * @_stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstrr, int _start, int _stop)
{
	static char buff[1024];
	int x = 0, y = 0;

	for (y = 0, x = _start; x < _stop; x++)
		if (pathstrr[x] != ':')
			buff[y++] = pathstrr[x];
	buff[y] = 0;
	return (buff);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the info struct
 * @pathstrr: the PATH string
 * @_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *inf, char *pathstrr, char *_cmd)
{
	int x = 0, cur_pos = 0;
	char *paths;

	if (!pathstrr)
		return (NULL);
	if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
	{
		if (is_cmd(inf, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!pathstrr[x] || pathstrr[x] == ':')
		{
			paths = dup_chars(pathstrr, cur_pos, x);
			if (!*paths)
				_strcat(paths, _cmd);
			else
			{
				_strcat(paths, "/");
				_strcat(paths, _cmd);
			}
			if (is_cmd(inf, paths))
				return (paths);
			if (!pathstrr[x])
				break;
			cur_pos = x;
		}
		x++;
	}
	return (NULL);
}
