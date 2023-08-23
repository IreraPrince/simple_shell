#include "shell.h"

/**
 **_strncpy - function that copies a string.
 *@dest:copy destination string
 *@src: original string
 *@n: amnt of char to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int f, h;
	char *j = dest;

	f = 0;
	while (src[f] != '\0' && f < n - 1)
	{
		dest[f] = src[f];
		f++;
	}
	if (f < n)
	{
		h = f;
		while (h < n)
		{
			dest[h] = '\0';
			h++;
		}
	}
	return (j);
}

/**
 **_strncat - function that Concatenates two strings.
 *@dest: first string.
 *@src:  second string.
 *@n: amnt of bytes to be used.
 *Return: concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, j;
	char *s = dest;

	k = 0;
	j = 0;
	while (dest[k] != '\0')
		k++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		k++;
		j++;
	}
	if (j < n)
		dest[k] = '\0';
	return (s);
}

/**
 **_strchr -function  points a character in a string.
 *@x: string to be parsed.
 *@c: char to look for
 *Return: (x) pntr to mem. areas
 */
char *_strchr(char *x, char c)
{
	do {
		if (*x == c)
			return (x);
	} while (x++ != '\0');

	return (NULL);
}
