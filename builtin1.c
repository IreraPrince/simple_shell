#include "shell.h"

/**
 * _myhistory -function Displays history list, one command by line.
 * @info: Structure containing potential arguments.
 *
 *  Return: 0 on success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function Sets alias to the string.
 * @info: param struct.
 * @str: the alias string .
 * Return:  0 on success, 1 on if htere is an error.
 */
int unset_alias(info_t *info, char *str)
{
	char *v, b;
	int ret;

	v = _strchr(str, '=');
	if (!v)
		return (1);
	b = *v;
	*v = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*v = b;
	return (ret);
}

/**
 * set_alias - function that sets alias to the string.
 * @info: param struct
 * @sraw: the alias string.
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *sraw)
{
	char *g;

	g = _strchr(sraw, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (unset_alias(info, sraw));

	unset_alias(info, sraw);
	return (add_node_end(&(info->alias), sraw, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string.
 * @node: the node alias.
 *
 * Return: 0 on success, 1 if theere is an error
 */
int print_alias(list_t *node)
{
	char *g = NULL, *n = NULL;

	if (node)
	{
		g = _strchr(node->str, '=');
		for (n = node->str; n <= g; n++)
		_putchar(*n);
		_putchar('\'');
		_puts(g + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function that mimics the alias builtin.
 * @info: Structure containing potential arguments.
 *
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *g = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		g = _strchr(info->argv[k], '=');
		if (g)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}
