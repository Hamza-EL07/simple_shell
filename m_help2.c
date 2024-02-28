#include "shell.h"

/**
 * m_help - Help information for the builtin help.
 * Return: no return
 */
void m_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _m_len_str(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _m_len_str(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _m_len_str(help));
}
/**
 * m_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void m_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _m_len_str(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _m_len_str(help));
}
/**
 * m_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void m_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _m_len_str(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _m_len_str(help));
}
