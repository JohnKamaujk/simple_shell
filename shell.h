#ifndef SHELL_H
#define SHELL_H

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

/* from string_funcs.c */
char *_stringtokenize(char *string, const char *delimeter);
int _stringcompare(char *str1, char *str2);
char *stringtrim(char *strin);

#endif /* SHELL_H */
