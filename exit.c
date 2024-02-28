#include "shell.h"

/**
 * exit_shell - function that handles exit builtin
 * @args: commands from the user
 * @argv: the name of the executable file
 * @token_count: number of tokens
 * @line: line to free
 * @val: exit value from previous command
 *
 * Return: void
 */
void exit_shell(char *args[], char *argv, int *token_count,
		char *line, int val)
{
	char *ptr;
	char *name = argv;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			/* convert exit status argument to an integer */
			long status = (int)strtol(args[1], &ptr, 10);

			if (args[1][0] == '-')
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", name, args[1]);
				free_tokens(&args, token_count);
				free(line);
				exit(2);
			}
			if (*ptr != '\0' || status == LONG_MIN || status == LONG_MAX)
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", name, args[1]);
				free_tokens(&args, token_count);
				free(line);
				exit(2);
			}
			else
			{
				free_tokens(&args, token_count);
				free(line);
				exit(status);
			}
		}
		else
		{
			free_tokens(&args, token_count);
			free(line);
			exit(val);
		}
	}
}


