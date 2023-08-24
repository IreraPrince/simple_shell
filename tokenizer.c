#include "shell.h"

/**
 * **strtow - splits string into words. function ignores repeat delimiters
 * @str: input string
 * @d: delimeter string
 * Return: On Success (array of strings), or NULL if it fails
 */

char **strtow(char *str, char *d)
{
	int p, q, r, t, numwords = 0;
	char **j;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (p = 0; str[p] != '\0'; p++)
		if (!is_delim(str[p], d) && (is_delim(str[p + 1], d) || !str[p + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	j = malloc((1 + numwords) * sizeof(char *));
	if (!j)
		return (NULL);
	for (p = 0, q = 0; q < numwords; q++)
	{
		while (is_delim(str[p], d))
			p++;
		r = 0;
		while (!is_delim(str[p + r], d) && str[p + r])
			r++;
		j[q] = malloc((r + 1) * sizeof(char));
		if (!j[q])
		{
			for (r = 0; r < q; r++)
				free(j[r]);
			free(j);
			return (NULL);
		}
		for (t = 0; t < r; t++)
			j[q][t] = str[p++];
		j[q][t] = 0;
	}
	j[q] = NULL;
	return (j);
}

/**
 * **strtow2 - function splits the string into words
 * @str: input string
 * @d: pntr to delimeter
 * Return: Success (array of strings), otherwise NULL
 */
char **strtow2(char *str, char d)
{
	int p, q, r, t, numwords = 0;
	char **j;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (p = 0; str[p] != '\0'; p++)
		if ((str[p] != d && str[p + 1] == d) ||
				    (str[p] != d && !str[p + 1]) || str[p + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	j = malloc((1 + numwords) * sizeof(char *));
	if (!j)
		return (NULL);
	for (p = 0, q = 0; q < numwords; q++)
	{
		while (str[p] == d && str[p] != d)
			p++;
		r = 0;
		while (str[p + r] != d && str[p + r] && str[p + r] != d)
			r++;
		j[q] = malloc((r + 1) * sizeof(char));
		if (!j[q])
		{
			for (r = 0; r < q; r++)
				free(j[r]);
			free(j);
			return (NULL);
		}
		for (t = 0; t < q; t++)
			j[q][t] = str[p++];
		j[q][t] = 0;
	}
	j[q] = NULL;
	return (j);
}

