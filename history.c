#include "shell.h"

/**
 * get_history_file -Function that gets the history file.
 * @info: param struct
 *
 * Return: success gives string containg history file.
 */

char *get_history_file(info_t *info)
{
	char *buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - function that creates file or appends to an existing file.
 * @info: param struct
 *
 * Return: 1 on success, otherwise -1.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history -file is read from the history.
 * @info: par struct.
 *
 * Return: success gives histcount else 0.
 */
int read_history(info_t *info)
{
	int w, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (w = 0; w < fsize; w++)
		if (buf[w] == '\n')
		{
			buf[w] = 0;
			build_history_list(info, buf + last, linecount++);
			last = w + 1;
		}
	if (last != w)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list -function that  Adds entry to a history linked list.
 * @info: Struct containing potential arguments.
 * @muf: pointer to buffer.
 * @linecount: pointer to history linecount.
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *muf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, muf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list following changes.
 * @info: Str containing potential arg.
 *
 * Return: success new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int b = 0;

	while (node)
	{
		node->num = b++;
		node = node->next;
	}
	return (info->histcount = b);
}
