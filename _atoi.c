#include "shell.h"

/**
 * interactive - pointer to shell interactive mode
 * @info: struct location.
 *
 * Return: 1 (for success), 0 (failure).
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks whether character is a delimeter.
 * @e: Character to check
 * @delim:pointer delimeter string.
 * Return: 1 (success), 0 (Failure).
 */
int is_delim(char e, char *delim)
{
	while (*delim)
		if (*delim++ == e)
			return (1);
	return (0);
}

/**
 * _isalpha -pointer to alphabetic character
 * @c:char to input
 * Return: 1 if c is alphabetic, 0 if it is not alphabetic
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function that converts string to an integer
 * @s: pointer to string to be converted
 * Return: 0
 */

int _atoi(char *s)
{
	int b, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (b = 0; s[b] != '\0' && flag != 2; b++)
	{
		if (s[b] == '-')
			sign *= -1;

		if (s[b] >= '0' && s[b] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[b] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
