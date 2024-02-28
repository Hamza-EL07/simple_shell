#include "shell.h"

/**
 * m_cd_dot - changes to the parent directory
 *
 * @varshell: data relevant (environ)
 *
 * Return: no return
 */
void m_cd_dot(shell_var *varshell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd_m, *m_cpstrtokpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd_m = _m_strdup(pwd);
	set_m_env("OLDPWD", cp_pwd_m, varshell);
	dir = varshell->args[1];
	if (_m_str_cmp(".", dir) == 0)
	{
		set_m_env("PWD", cp_pwd_m, varshell);
		free(cp_pwd_m);
		return;
	}
	if (_m_str_cmp("/", cp_pwd_m) == 0)
	{
		free(cp_pwd_m);
		return;
	}
	m_cpstrtokpwd = cp_pwd_m;
	rev_string(m_cpstrtokpwd);
	m_cpstrtokpwd = _m_strtok(m_cpstrtokpwd, "/");
	if (m_cpstrtokpwd != NULL)
	{
		m_cpstrtokpwd = _m_strtok(NULL, "\0");

		if (m_cpstrtokpwd != NULL)
			rev_string(m_cpstrtokpwd);
	}
	if (m_cpstrtokpwd != NULL)
	{
		chdir(m_cpstrtokpwd);
		set_m_env("PWD", m_cpstrtokpwd, varshell);
	}
	else
	{
		chdir("/");
		set_m_env("PWD", "/", varshell);
	}
	varshell->status = 0;
	free(cp_pwd_m);
}

/**
 * m_cd_to - changes to a directory given
 * by the user
 *
 * @varshell: data relevant (directories)
 * Return: no return
 */
void m_cd_to(shell_var *varshell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd_m, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = varshell->args[1];
	if (chdir(dir) == -1)
	{
		m_get_error(varshell, 2);
		return;
	}

	cp_pwd_m = _m_strdup(pwd);
	set_m_env("OLDPWD", cp_pwd_m, varshell);

	cp_dir = _m_strdup(dir);
	set_m_env("PWD", cp_dir, varshell);

	free(cp_pwd_m);
	free(cp_dir);

	varshell->status = 0;

	chdir(dir);
}

/**
 * m_cd_previous - changes to the previous directory
 *
 * @varshell: data relevant (environ)
 * Return: no return
 */
void m_cd_previous(shell_var *varshell)
{
	char pwd[PATH_MAX];
	char *p_pwd, *m_old_pwd, *cp_pwd_m, *cm_old_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd_m = _m_strdup(pwd);

	m_old_pwd = _get_m_env("OLDPWD", varshell->_environ);

	if (m_old_pwd == NULL)
		cm_old_pwd = cp_pwd_m;
	else
		cm_old_pwd = _m_strdup(m_old_pwd);

	set_m_env("OLDPWD", cp_pwd_m, varshell);

	if (chdir(cm_old_pwd) == -1)
		set_m_env("PWD", cp_pwd_m, varshell);
	else
		set_m_env("PWD", cm_old_pwd, varshell);

	p_pwd = _get_m_env("PWD", varshell->_environ);

	write(STDOUT_FILENO, p_pwd, _m_len_str(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd_m);
	if (m_old_pwd)
		free(cm_old_pwd);

	varshell->status = 0;

	chdir(p_pwd);
}

/**
 * m_cd_to_home - changes to home directory
 *
 * @varshell: data relevant (environ)
 * Return: no return
 */
void m_cd_to_home(shell_var *varshell)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _m_strdup(pwd);

	home = _get_m_env("HOME", varshell->_environ);

	if (home == NULL)
	{
		set_m_env("OLDPWD", p_pwd, varshell);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		m_get_error(varshell, 2);
		free(p_pwd);
		return;
	}

	set_m_env("OLDPWD", p_pwd, varshell);
	set_m_env("PWD", home, varshell);
	free(p_pwd);
	varshell->status = 0;
}
