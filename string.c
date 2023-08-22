#include "shell.h"

/**
 * _strlen - function rtrns length of string
 * @s: pntr to a string whose length to check
 *
 * Return: integer string length
 */
int _strlen(char *s)
{
	int q = 0;

	if (!s)
		return (0);

	while (*s++)
		q++;
	return (q);
}

/**
 * _strcmp - function executes lexicogarphic comparison of two strangs.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - function confirms if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: pntr of the  next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - function concatenates the two strings
 * @dest: end bfr
 * @src: origin bfr
 *
 * Return: pntr to the end bfr
 */
char *_strcat(char *dest, char *src)
{
	char *end = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (end);
}

