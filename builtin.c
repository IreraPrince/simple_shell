#include "shell.h"

/**
 * _myexit - function Exits the shell.
 * @info: Structure containing potential argument.
 *
 * Return: Exits with a given exit status.
 * (0) if info.argv[0] != "exit".
 */
int _myexit(info_t *info)
{
	int exitshell;

	if (info->argv[1]) /* Whether there is an exit arguement */
	{
		exitshell = _erratoi(info->argv[1]);
		if (exitshell == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the process of current directory.
 * @info: pointer to Structure containing potential arguments.
 *
 * Return: 0
 */
int _mycd(info_t *info)
{
	char *a, *di, bufr[1024];
	int chdir_ret;

	a = getcwd(bufr, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		di = _getenv(info, "HOME=");
		if (!di)
			chdir_ret = /* TODO: what should this be? */
				chdir((di = _getenv(info, "PWD=")) ? di : "/");
		else
			chdir_ret = chdir(di);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((di = _getenv(info, "OLDPWD=")) ? di : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(bufr, 1024));
	}
	return (0);
}

/**
 * _myhelp -process that changes current directory
 * @bwiza: pointer to Structure containing potential arguments.
 *
 * Return: success 0
 */
int _myhelp(bwiza_t *bwiza)
{
	char **arg_array;

	arg_array = bwiza->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
