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

/* from get_line */
ssize_t getline(char **linepointer, size_t *ptr, FILE *stream);

/* from parser */
void parser(char *input_str, char **args);

#define MAX_INPUT_LENGTH 256
#define BUFF_SIZE 1024

#endif /* SHELL_H */
