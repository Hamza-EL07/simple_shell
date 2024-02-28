#include "shell.h"

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_var varshell;
	(void)ac;

	signal(SIGINT, get_sign_int);
	m_set_data(&varshell, av);
	m_sh_loop(&varshell);
	m_freedata(&varshell);
	if (varshell.status < 0)
		return (255);
	return (varshell.status);
}
