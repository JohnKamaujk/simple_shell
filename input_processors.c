#include "header.h"

/**
 * path_finder - finds and breaks a path into an array of directories.
 * Return: a pointer to the current path.
 */

char **path_finder(void)
{
	size_t i = 0, j = 0, check = 0;
	char path[] = "PATH=";
	char colon[] = ":";
	char **current_path;
	char *nopath = "nopath";

	while (environ[i] != NULL)
	{
		check = 0;
		while (environ[i][j] == path[j] && path[j] != '\0')
		{
			j++;
			check++;
		}
		if (check == 5)
		{
			current_path = parsers(&environ[i][j], colon);
			if (current_path == NULL)
				return (NULL);
			return (current_path);
		}
		else
			j = 0;
		i++;
	}
	current_path = malloc(sizeof(char *) * 2);
	if (current_path == NULL)
		return (NULL);
	current_path[0] = malloc(sizeof(char) * (string_length(nopath) + 1));
	if (current_path[0] == NULL)
	{
		free(current_path);
		return (NULL);
	}
	current_path[0] = string_duplicator(nopath, current_path[0]);
	current_path[1] = NULL;
	return (current_path);
}

/**
 * path_checker - a function to check that the pathis valid
 * @current_path: our current path options one at a time
 * @command: our current command form argv[0]
 * @fail_count: int that tells us if stat failed once
 * @path_trailer: pointer to determine if tmpPATH = command
 * after checking against full PATH (including ::)
 * Return: a character pointer to the valid path + cmd
 * concatonated
 */
char *path_checker(char **current_path, char *command,
int fail_count, int *path_trailer)
{
	int i = 0, check1, check2;
	char *tmpPath;
	struct stat buf;

	*path_trailer = 0;
	if (current_path == NULL)
		return (NULL);
	while (current_path[i] != NULL && str_comp(current_path[i], "nopath"))
	{
		tmpPath = str_concat(current_path[i], command);
		check1 = stat(tmpPath, &buf);
		check2 = access(tmpPath, X_OK) + check1;
		if (check2 == 0)
		{
			free_args(&current_path);
			return (tmpPath);
		}
		if (check1 == 0 && fail_count == 1)
		{
			free_args(&current_path);
			return (tmpPath);
		}
		i++;
		free(tmpPath);
	}
	if (str_comp(current_path[0], "\0") ||
	str_comp(current_path[0], "nopath") == 0)
	*path_trailer = 1;
	free_args(&current_path);
	tmpPath = malloc(sizeof(char) * (string_length(command) + 1));
	if (tmpPath == NULL)
		error_mallocexit();
	for (i = 0; command[i]; i++)
		tmpPath[i] = command[i];
	tmpPath[i] = '\0';
	return (tmpPath);
}

/**
 * str_concat - a function to concatonate two strings
 * @s1: the first string, in this case each option in
 * our path one option at a time.
 * @s2: our command form argv[0]
 * Return: a char pointer to our concatonated string.
 */

char *str_concat(char *s1, char *s2)
{
	int i = 0, j = 0, length1 = 0, length2 = 0, total = 0;
	char *concat;

	if (s1 != NULL)
	{
		length1 += string_length(s1);
		if (length1 == 0)
			s1 = "";
	}
	else
		s1 = "";
	if (s2 != NULL)
		length2 += string_length(s2);
	else
		s2 = "";
	total = length1 + length2 + 2;
	concat = (char *) malloc(total * (sizeof(char)));
	if (concat == NULL)
		return (NULL);
	for (i = 0; i < length1; i++, j++)
		concat[j] = s1[i];
	if (j != 0)
	{
		concat[j] = '/';
		j++;
	}
	for (i = 0; i < length2; i++, j++)
	{
		concat[j] = s2[i];
	}
	concat[j] = '\0';
	return (concat);
}


/**
 * printenv - a function to print out the current enviroment
 * @buffer: buffer with input read into shell
 * @args: 2D array with arguments, including program program_name
 * @returned_status: input status of previous command
 * @program_name: program_name of currently running shell program
 */

void printenv(char **buffer, char ***args, int *returned_status,
char **program_name)
{
	int i = 0;
	ssize_t  w;
	char newline[] = "\n";

	(void)buffer;
	(void)args;
	(void)program_name;

	*returned_status = 0;
	if (environ == NULL)
	{
		perror("ERROR: Enviroment unset or unrecognized.\n");
		return;
	}
	while (environ[i] != NULL)
	{
		w = write(STDOUT, environ[i], string_length(environ[i]));
		if (w < 0)
			error_writter();
		w = write(STDOUT, newline, string_length(newline));
		if (w < 0)
			error_writter();
		i++;
	}
}


