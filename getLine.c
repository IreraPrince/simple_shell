#include "shell.h"

/**
 * input_buf - function that buffers chained commands.
 * @info: Param struct.
 * @buf: location of buffer.
 * @len: location of length variable.
 * Return: bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _getline(info, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0'; /* remove trailing newline */
				w--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = w;
				info->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * get_input - function that gets a line minus the newline
 * @info: param struct
 *
 * Return: byte read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		p = buf + a; /* get pointer for return */

		check_chain(info, buf, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - function that reads a buffer
 * @info: para struct
 * @buf: buff
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - function that gets the next line of input from STDIN
 * @info: param struct
 * @ptr: location of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: o
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, o = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		o = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, o, o ? o + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (o)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	o += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = o;
	*ptr = p;
	return (o);
}

/**
 * SigintHandler -function that blocks ctrl-C
 * @num: the signal num
 *
 * Return: void
 */
void SigintHandler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
