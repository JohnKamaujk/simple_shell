#include "header.h"
/**
 * handle_exit_command - Handle the "exit" command.
 *
 * @args: array of tokenized arguments
 * @returned_status: pointer to the returned status variable
 */
void handle_exit_command(char **args)
{
	if (args[1] != NULL)
	{
		int exit_status = _atoi(args[1]);

		free_args(&args);
		exit(exit_status);
	}
	else
	{
		free_args(&args);
		exit(0);
	}
}

/**
 * main - Reads from DATAIN, parses, and executes.
 *
 * @argc: argument count
 * @argv: argument variables
 *
 * Return: 0 (success)
 */
int main(int argc, char **argv)
{
	char *program_name = malloc(sizeof(char) * (string_length(argv[0]) + 1));
	char *buffer, *path, **args, *spacer = " ";
	ssize_t BUFF_SIZE = 1024;
	int input_data = 0, check_path = 0, returned_status = 0, lc = 0, i = 0;
	(void)argc;
	program_name = string_duplicator(argv[0], program_name);
	while (1)
	{
		if (isatty(DATAIN))
			input_data = prompt_printer(&program_name);
		signal(SIGINT, &signal_interrupt);
		buffer = malloc(sizeof(char) * BUFF_SIZE);
		if (buffer == NULL)
			malloc_error(&program_name);
		line_reader(&buffer, &BUFF_SIZE, DATAIN, input_data, returned_status,
		&program_name);
		while (buffer != NULL)
		{
			lc++;
			args = parsers(buffer, spacer);
			if (args == NULL)
				malloc_error(&program_name);
			for (i = 0; args[i]; i++)
			{
				if (str_comp(args[i], "exit") == 0 || str_comp(args[i], "\nexit") == 0)
				{
					free(args[i]);
					args[i] = NULL;
					handle_exit_command(args);
				}
			}
			buffer = reset(&buffer, &args, spacer, &lc);
			builtiin_executable(&buffer, &args, &path, &returned_status, &check_path,
			lc, &program_name);
			free_path_args(&path, &check_path, &args);
		}
		free(buffer);
	}
	return (returned_status);
}

/**
 * bultiin_executable - function to match command to builtin
 * and run builtin program
 * or to check if command is an executable program and run that
 * @buffer: input pointer to buffer read to in line_reader
 * @args: input array of tokenized arguments
 * @path: input pointer to string to set path to before executing
 * @returned_status: input status of previously run command
 * @check_path: input pointer to variable to indicate if path is set in mem
 * @lc: input integer of line count
 * @program_name: name of the running shell program
 */

void builtiin_executable(char **buffer, char ***args, char **path,
int *returned_status, int *check_path, int lc, char **program_name)
{
	int i = 0;
	program_data builtins[] = { {"exit", exiter}, {"env", printenv},
				   {"\n", newline}, {NULL, NULL} };

	for (i = 0; builtins[i].program_name; i++)
	{
		if ((str_comp((*args)[0], builtins[i].program_name)) == 0)
		{
			builtins[i].func(buffer, args, returned_status, program_name);
			break;
		}
		if (builtins[i + 1].program_name == NULL)
		{
			*check_path = 1;
			exe_fork(path, args, buffer, returned_status, lc, program_name);
					if (*returned_status == 0)
						*returned_status = executer(path, args, buffer);
				}
			}
}

/**
 * signal_interrupt - catches Ctrl+C and, instead of stopping shell,
* it writes a newline and prompts the user again
* @signal: input signal to confirm is SIGINT
*/

void signal_interrupt(int signal)
{
	char *new_prompt = "\n$ ";

	if (signal == SIGINT)
	{
		if (isatty(DATAIN))
			write(DATAOUT, new_prompt, string_length(new_prompt));
	}
}
