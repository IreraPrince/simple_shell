#include "shell.h"

/**
 * is_chain - function checks if current chrctr in buffer is chain delimeter
 * @info: prmtr struct
 * @buf: chrctr buffer
 * @p: pntr of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 on failure
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - confirms if chaining should continue based on last status
 * @info: prmtr struct
 * @buf: chrctr buffer
 * @p: location of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * replace_alias - function replaces aliases in the tokenized string
 * @info: pntr to the prmtr struct
 *
 * Return: 1 Successful, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - function replaces vars tokenized string
 * @info: pointer to the prmtr struct
 *
 * Return: 1 on success, 0 failure
 */
int replace_vars(info_t *info)
{
	int z = 0;
	list_t *node;

	for (z = 0; info->argv[z]; z++)
	{
		if (info->argv[z][0] != '$' || !info->argv[z][1])
			continue;

		if (!_strcmp(info->argv[z], "$?"))
		{
			replace_string(&(info->argv[z]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[z], "$$"))
		{
			replace_string(&(info->argv[z]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[z][1], '=');
		if (node)
		{
			replace_string(&(info->argv[z]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[z], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - function replaces a string
 * @old: location of the old string
 * @new: refers to a new string
 *
 * Return: 1 when Successful, 0 on failure
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

