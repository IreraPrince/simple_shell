#include "shell.h"

/**
 * _strcpy - function copies a string
 * @dest: pntr to end
 * @src: pntr to origin
 *
 * Return: pointer to end
 */
char *_strcpy(char *dest, char *src)
{
	int q = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[q])
	{
		dest[q] = src[q];
		q++;
	}
	dest[q] = 0;
	return (dest);
}

/**
 * _strdup - duplicates the string
 * @str: pntr to the string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *end;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	end = malloc(sizeof(char) * (l + 1));
	if (!end)
		return (NULL);
	for (l++; l--;)
		end[l] = *--str;
	return (end);
}

/**
 * _puts - function prints input string
 * @str: pointer the string to be printed
 *
 * Return: 0
 */
void _puts(char *str)
{
	int q = 0;

	if (!str)
		return;
	while (str[q] != '\0')
	{
		_putchar(str[q]);
		q++;
	}
}

/**
 * _putchar - function writes chrtr C to stdout
 * @c: pntr to chrtr to print
 *
 * Return: Success 1, otherwise error -1 where errno is applied
 */
int _putchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

