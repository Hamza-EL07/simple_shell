#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

extern char **environ;

int _putchar(char);
void _puts(char *str);

char *_str_chr(char *str, char c);
int _str_leng(const char *str);
char *_str_cpy(char *target, const char *sorc);
char *_str_cat(char *target, const char *sorc);
int _str_cmp(const char *s1, const char *s2);

char *_get_environ(const char *env_var);
char **parse_cmd(char *cmnd, char *dlm);
char *check_cmd(char *cmd);
char *custom_strdup(const char *str);
void exec_cmd(char **args);

#endif
