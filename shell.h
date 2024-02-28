#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_delimtr " \t\r\n\a"
#define PATH_MAX 4096

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_var;

/**
 * struct m_sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct m_sep_list_s
{
	char separator;
	struct m_sep_list_s *next;
} m_sep_list;

/**
 * struct m_line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct m_line_list_s
{
	char *line;
	struct m_line_list_s *next;
} m_line_list;

/**
 * struct m_r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct m_r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct m_r_var_list *next;
} r_var;

/**
 * struct m_builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct m_builtin_s
{
	char *name;
	int (*f)(shell_var *varshell);
} m_builtin_t;

/* m_data.c */
void m_freedata(shell_var *varshell);
void m_set_data(shell_var *varshell, char **av);
r_var *m_addnodervar(r_var **_mhead, int l_var, char *var, int m_l_val);
void m_freelistrvar(r_var **_mhead);

/* m_mlists.c */
m_sep_list *m_addsepnodeend(m_sep_list **_mhead, char sep);
void m_freeseplist(m_sep_list **_mhead);
m_line_list *m_addlinenodeend(m_line_list **_mhead, char *line);
void m_freelinelist(m_line_list **_mhead);
void rev_string(char *s);

/* m_str functions */
char *_m_strcat(char *dest, const char *src);
char *_m_strcpy(char *dest, char *src);
int _m_str_cmp(char *s1, char *s2);
char *_m_str_chr(char *s, char c);
int _m_str_spn(char *s, char *accept);

/* m_memr.c */
void _m_memry_cpy(void *new_ptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc_dp(char **ptr, unsigned int old_size, unsigned int new_size);

/* m_strtwo.c */
char *_m_strdup(const char *s);
int _m_len_str(const char *s);
int m_cmp_chars(char str[], const char *delimtr);
char *_m_strtok(char str[], const char *delimtr);
int _m_is_digit(const char *s);

/* m_err.syntx.c */
int m_repeat_char(char *input, int i);
int m_error_sep_op(char *input, int i, char last);
int m_frst_ch(char *input, int *i);
void m_print_syntx_err(shell_var *varshell, char *input, int i, int bool);
int m_check_syntx_err(shell_var *varshell, char *input);

/* m_sh_loop.c */
char *without_comment(char *in);
void m_sh_loop(shell_var *varshell);
int m_exc_lin(shell_var *varshell);
int m_cd_sh(shell_var *varshell);

/* m_split.c */
char *swap_m_ch(char *input, int bool);
void m_addnodes(m_sep_list **_mhead_s, m_line_list **_mhead_l, char *input);
void m_go_to_next(m_sep_list **list_s, m_line_list **list_l,
									shell_var *varshell);
int m_splt_cmd(shell_var *varshell, char *input);
char **m_splt_line(char *input);

/* m_rep_var.c */
void m_chck_env(r_var **h, char *in, shell_var *data);
int m_chck_vars(r_var **h, char *in, char *st, shell_var *data);
char *m_replace_input(r_var **_mhead, char *input, char *new_input, int nlen);
char *m_rep_var(char *input, shell_var *varshell);

/* m_get_ln.c */
void as_ln(char **ptr_line, size_t *n, char *buffer, size_t j);
ssize_t get_ln(char **ptr_line, size_t *n, FILE *strmfile);
char *read_m_line(int *meof);
void get_sign_int(int sign);
int get_my_help(shell_var *varshell);

/* m_excmd.c */
int is_m_cdir(char *path, int *i);
char *_m_which(char *cmd, char **_environ);
int is_m_executable(shell_var *varshell);
int chck_m_err_cmd(char *dir, shell_var *varshell);
int cmd_m_exec(shell_var *varshell);

/* m_env.c */
char *_get_m_env(const char *name, char **_environ);
int _env(shell_var *varshell);

/* m_envtwo.c */
char *copy_m_info(char *name, char *value);
void set_m_env(char *name, char *value, shell_var *varshell);
int _m_setenv(shell_var *varshell);
int _m_unsetenv(shell_var *varshell);

/* m_cd.c */
void m_cd_dot(shell_var *varshell);
void m_cd_to(shell_var *varshell);
void m_cd_previous(shell_var *varshell);
void m_cd_to_home(shell_var *varshell);

/* m_get_buil */
int m_exit_sh(shell_var *varshell);
int (*m_get_buil(char *cmd))(shell_var *varshell);
int m_get_len(int n);
char *m_itoa(int n);
int _m_atoi(char *s);

/* m_error.c */
char *m_str_cat_cs(shell_var *, char *, char *, char *);
char *m_err_get_cd(shell_var *varshell);
char *m_err_notfound(shell_var *varshell);
char *m_err_exit_sh(shell_var *varshell);
char *m_env_err(shell_var *varshell);

/* m_errorone.c */
char *m_err_path(shell_var *varshell);
int m_get_error(shell_var *varshell, int eval);

/* m_help.c */
void m_envhelp(void);
void m_set_m_envhelp(void);
void m_unset_m_envhelp(void);
void m_gen_help(void);
void m_exithelp(void);

/* m_help2.c */
void m_help(void);
void m_help_alias(void);
void m_help_cd(void);

#endif
