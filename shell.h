#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "term_log.c"

char *args[64];
pid_t x;
int status;
// char line[1024];

#define PROMPT "user$"
void term_prompt ();
char term_log (const char *c);


#endif