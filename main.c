#include "shell.h"

/**
 * main - function process arguments command count and vector
 * @ac: arg count
 * @av: arg vector
 *
 * Return: Success gives 0 while error gives 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int dif = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (dif)
			: "r" (dif));

	if (ac == 2)
	{
		dif = open(av[1], O_RDONLY);
		if (dif == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = dif;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

