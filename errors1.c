#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer.
 * @s:string to be converted.
 * Return: 0 if no no. in string, converted num otherwise -1 on error.
 */
int _erratoi(char *s)
{
	int g = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (g = 0;  s[g] != '\0'; g++)
	{
		if (s[g] >= '0' && s[g] <= '9')
		{
			result *= 10;
			result += (s[g] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error -function that Prints an error message.
 * @info: The param & return info struct.
 * @estr:pointer to string containing specified error type.
 * Return: 0 if no num in string, converted or -1 on error.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: the file descriptor.
 *
 * Return: number of char printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int p, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{

	_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p = 1000000000; p > 1; p /= 10)
	{
		if (_abs_ / p)
		{
			__putchar('0' + current / p);
			count++;
		}
		current %= p;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - function that converter function, a clone of itoa
 * @num: numb
 * @base: base
 * @flags: argument flag.
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments -replaces first instance of '#' with '\0'
 * @buf: Location of the string to modify
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}
