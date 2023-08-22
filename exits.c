#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates two strings.
 *@dest: the first string.
 *@src: the second string.
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
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
 **_strchr - Locates a character in a string.
 *@x: the string to be parsed.
 *@c: the character to look for
 *Return: (x) a pointer to the memory area s
 */
char *_strchr(char *x, char c)
{
	do {
		if (*x == c)
			return (x);
	} while (x++ != '\0');

	return (NULL);
}
