#ifndef _ALL_H_
#define _ALL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

/* Define a macro for string (if str is NULL, use "(null)") */
#define STRING ((str) ? str : "(null)")

/* Define a structure to hold various parameters */
typedef struct para
{
	char **envp;
	char **pwd;
	char *line;
	char *shell_name;
	char *path;
	char *old_pwd;
	int n_token;
	int n_path;
	int status;
	int count;
	int pid;
	int file;
} para;

/* declaration of Functions */
void handle_dots(char **line, para *args);
void print_number(int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void tostring(char *str, int num);
void space(char **line, para *args);
void handle_dollar(char *buffer, char **dollar, para *args);
void change_pwd(para *args);
void free_exit(para *args);
int _printf(const char *format, ...);
int print_string(char *s);
int print_char(char c);
int num_len(int n);
int specifier(char c, va_list args);
int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(char *str1, char *str2);
int _atoi(char *s);
int _exit_(para *args);
int _command_(para *args);
int _execeve(para *args, char *buff);
int input(para *args, int arrow, int *semi);
int token(char *line, char *delim);
int rev_cmp(char *s1, char *s2);
int _env(para *args);
int handle_input(para *args);
int cd(para *args);
char *_strcat(char *dest, char *src);
char *_strdup(para *args, char *str);
char *_strtok(char *str, const char *delim);
char *_strchr(char *s, char c);
char *_strncat(char *dest, char *src, int n);
char *handle_realloc(para *args, char *buffer, int *buffer_size, int extra, int max);
char *_get_env(char **envp, char *env, int len);
char **get_PWD(para *args);
char *_malloc(para *args, int size);
char *malloc2(char *line, para *args, int size);
ssize_t _getline(para *args);
#endif
