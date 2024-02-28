#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define BUFSIZE 64
#define TOKEN_BUFSIZE 64

#define PATH_LENGTH 1024
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

extern char **environ;

int set_exit_code(int);
int get_and_clean_line(char *, size_t *);
int exit_value(int);
int create_child(char **, char *);
void get_tokens(const char *, int *, char ***);
void free_tokens(char ***, int *);
void exit_shell(char *args[], char *, int *, char *, int);
void tokenize_str(char *, char ***, int *);
void tokenize_commands(char *, char ***, int *);
void tokenize_string(char *, char ***, int *);
char *find_command(const char *, char *);
char *get_location(char *);
char **split_line(char *);
char *custom_strdup(char *);
void builtin_commands(char **);
void set_env(char **);
void unset_env(char **);
int chagedir(char **, char *);
int handle_commands(char **, int *, char *, char *);
int is_variable_to_exclude(const char *);
void print_env(char **);
int compare_strings(const void *, const void *);

#endif

