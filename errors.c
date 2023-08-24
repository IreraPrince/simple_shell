#include "shell.h"

/**
 * _eputs - function prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int u = 0;

	if (!str)
		return;
	while (str[u] != '\0')
	{
		_eputchar(str[u]);
		u++;
	}
}

/**
 * _eputchar - function that writes the character c to stderr
 * @c: char to print
 *
 * Return: if it is true 1.On error, -1 is returned,
 */
int _eputchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

/**
 * _putfd - function that writes the character c to given fd.
 * @c: char to print.
 * @fd: The file descriptor to write to
 *
 * Return: 1 On success, On error, -1 is returned.
 */
int _putfd(char c, int fd)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(fd, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

/**
 * _putsfd - function prints an input string.
 * @str: string to be printed
 * @fd: the file descriptor to write
 *
 * Return: number of chars put.
 */
int _putsfd(char *str, int fd)
{
	int r = 0;

	if (!str)
		return (0);
	while (*str)
	{
		r += _putfd(*str++, fd);
	}
	return (r);
}
