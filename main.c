#include "shell.h"

/**
 * main - main function
 * Return: 0
 */

int main(void)
{

	char *bf;
	size_t sz_bf = 0;
	char **args;

	while (1)
	{
		printf("#cisfun$ ");

		if (getline(&bf, &sz_bf, stdin) == -1)
		{
			write(1, "\n", 1);
			exit(1);
		}

		args = parse_cmd(bf, " \t\n");

		if (_str_cmp(args[0], "exit") == 0)
		{
			free(bf);
			free(args);
			exit(0);
		}
		else if (_str_cmp(args[0], "env") == 0)
		{
			char **env_ptr = environ;

			while (*env_ptr != NULL)
			{
				printf("%s\n", *env_ptr);
				env_ptr++;
			}
		}
		else
			exec_cmd(args);
		free(args);
	}

	return (0);
}
