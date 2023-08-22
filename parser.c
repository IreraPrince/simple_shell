#include "shell.h"

/**
 * is_cmd - function decides if it is an executable command file
 * @info: info struct
 * @path: direction of file
 *
 * Return: 1 if succesful, 0 on failure
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function duplicate the characters
 * @pathstr: path string
 * @start: where index begins
 * @stop: where index ends
 *
 * Return: a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buffer[y++] = pathstr[x];
	buffer[y] = 0;
	return (buffer);
}

/**
 * find_path - function locates commands in PATH string
 * @info: info struct
 * @pathstr: a string path
 * @cmd: finds command
 *
 * Return: full PATH cmd found (Success) or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = dup_chars(pathstr, curr_pos, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}

