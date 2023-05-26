#ifndef HEADER_H
#define HEADER_H

extern char **environ;

/* allowed_liblaries */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>


/* definations and strucks */
#define DATAERROR STDERR_FILENO
#define DATAIN STDIN_FILENO
#define DATAOUT STDOUT_FILENO
#define last (*buffer)[count - 1]
#define Non_Path ((*path)[0] != '/' && (*path)[0] != '.' && (*path)[0] != '~')
#define Non_Delim (buffer[j] != delim[0] && buffer[j] != '\0')

/**
 * struct program_data - matches input command to builtin or sends to execute
 * @program_name: program_name of the built-in or newline
 * @func: function pointer to built-in
 *
 */

typedef struct program_data
{
	char *program_name;
	void (*func)(char **buffer, char ***args, int *returned_status,
	char **program_name);
} program_data;



int _atoi(const char *str);
int string_length(char *s);
char *string_duplicator(char *input, char *program_name);
int prompt_printer(char **program_name);
void signal_interrupt(int signal);
ssize_t line_reader(char **buffer, ssize_t *buffsize, FILE *stdin,
		 int user_input, int stat_check, char **program_name);
char *realocater(char *buffer, size_t count);
char **parsers(char *buffer, char *delim);
ssize_t arg_counting(char **buffer, char *delim);
char *reset(char **buffer, char ***args, char *delim, int *lc);
void builtiin_executable(char **buffer, char ***args, char **path,
int *returned_status, int *check_path,
int lc, char **program_name);
int str_comp(char *s1, char *s2);
void printenv(char **buffer, char ***args,
int *returned_status, char **program_name);

void exiter(char **buffer, char ***args,
int *returned_status, char **program_name);

void newline(char **buffer, char ***args,
int *returned_status, char **program_name);

void exe_fork(char **path, char ***args, char **buffer,
int *returned_status, int lc, char **program_name);

char *int2char(int num);
int power(int base, int exp);
char **path_finder(void);
char *path_checker(char **ourpath, char *command, int fail_count,
int *path_trailer);
char *str_concat(char *ourpath, char *command);
int executer(char **path, char ***args, char **buffer);
void free_args(char ***args);
void free_path_args(char **path, int *check_path, char ***args);
void malloc_error(char **program_name);
void error_mallocexit(void);
void error_readliner(char **program_name);
void error_writter(void);
void c_d(char *name);

#endif
