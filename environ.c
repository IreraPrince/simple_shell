#include "shell.h"

/**
 * _myenv -function that prints current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environ variable.
 * @info: Structure containing potential arguments.
 * @ame: env var name
 *
 * Return: The value
 */
char *_getenv(info_t *info, const char *ame)
{
	list_t *node = info->env;
	char *d;

	while (node)
	{
		d = starts_with(node->str, ame);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Function that Initialize a new environment variable.
 *
 * @info: Structure containing potential arguments.
 *
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function that Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int t;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (t = 1; t <= info->argc; t++)
		_unsetenv(info, info->argv[t]);

	return (0);
}

/**
 * populate_env_list - function that Populates env linked list.
 * @busy: Structure containing potential arguments.
 *
 * Return: 0
 */
int populate_env_list(busy_t *busy)
{
	list_t *node = NULL;
	size_t r;

	for (r = 0; environ[r]; r++)
		add_node_end(&node, environ[r], 0);
	busy->env = node;
	return (0);
}
