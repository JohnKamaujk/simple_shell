#include "header.h"

/**
 * prompt_printer - prints $ to accept input
 * @program_name: name of our compiled program
 * Return: 1 if successful to set user_input
 */

int prompt_printer(char **program_name)
{
	char *prompt = "$ ";
	ssize_t w = 0;

	w = write(STDOUT, prompt, string_length(prompt));
	if (w < 0)
	{
		free((*program_name));
		error_writter();
		return (-1);
	}

	return (1);
}

/**
 * malloc_error - prints error message and exits when malloc fails
 * @program_name: the program_name of our compiled program
 */

void malloc_error(char **program_name)
{
	/* Error message from malloc man page, exit status from ENOMEM */
	char *string = "ENOMEM Out of memory.";

	free((*program_name));
	write(STDERR, string, string_length(string));
	exit(12);
}

/**
 * error_mallocexit - prints error message and exits when malloc fails
 */

void error_mallocexit(void)
{
	/*Error message from malloc man page, exit status from ENOMEM */
	char *string = "ENOMEM Out of memory.";

	write(STDERR, string, string_length(string));
}


/**
 * error_readliner - prints error message and exits when getline fails
 * @program_name: program_name of currently running shell program
 */

void error_readliner(char **program_name)
{
	/*Error message from getline man page, exit status from EINVAL */
	free(program_name);
	perror("EINVAL Bad arguments\n");
	exit(22);
}
/**
 * error_writter - a fucntion to wrtie and error if write fails.
 */
void error_writter(void)
{
	/* Error message from any function with a write() for if the write fails */
	perror("ERROR: write failed.\n");
	exit(450);
}
