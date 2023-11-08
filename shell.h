#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} lis_t;

typedef struct passinf
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        lis_t *env;
        lis_t *history;
        lis_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} inf_t;

#define inf_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

typedef struct builtin
{
        char *type;
        int (*func)(inf_t *);
        int (*func)(inf_t *);
} builtin_table;


int hsh(inf_t *, char **);
int find_builtin(inf_t *);
void find_cmd(inf_t *);
void fork_cmd(inf_t *);

int is_cmd(inf_t *, char *);

char *dup_chars(char *, int, int);
char *find_path(inf_t *, char *, char *);

int loophsh(char **);

void e_puts(char *);
int e_putchar(char);
int e_putfd(char c, int fd);
int e_putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *strncpy(char *, char *, int);
char *strncat(char *, char *, int);
char *strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int isInteractive(inf_t *);
int isDelimiteriter(char, char *);
int isAlpha(int);
int stringToInteger(char *);

int _erratoi(char *);
void print_error(inf_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(inf_t *);
int _mycd(inf_t *);
int _myhelp(inf_t *);

int _myhistory(inf_t *);
int _myalias(inf_t *);

ssize_s get_input(inf_t *);
int _getline(inf_t *, char **, size_s *);
void sigintHandler(int);

void clear_inf(inf_t *);
void set_inf(inf_t *, char **);
void free_inf(inf_t *, int);

char *_getenv(inf_t *, const char *);
int _myenv(inf_t *);
int mysetenv(inf_t *);
int myunsetenv(inf_t *);
int populate_env_list(inf_t *);

char **get_environ(inf_t *);
int _unsetenv(inf_t *, char *);
int setenv(inf_t *, char *, char *);

char *get_history_file(inf_t *inf);
int write_history(inf_t *inf);
int read_history(inf_t *inf);
int build_history_list(inf_t *inf, char *buf, int linecount);
int renumber_history(inf_t *inf);

lis_t *add_node(lis_t **, const char *, int);
lis_t *add_node_end(lis_t **, const char *, int);
size_s print_list_str(const lis_t *);
int delete_node_at_index(lis_t **, unsigned int);
void free_list(lis_t **);

size_s list_len(const lis_t *);
char **lis_to_strings(lis_t *);
size_s print_list(const lis_t *);
lis_t *node_starts_with(lis_t *, char *, char);
ssize_s get_node_index(lis_t *, lis_t *);

int is_chain(inf_t *, char *, size_s *);
void check_chain(inf_t *, char *, size_s *, size_s, size_s);
int replace_alias(inf_t *);
int replace_vars(inf_t *);
int replace_string(char **, char *);

#endif
