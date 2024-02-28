#include "shell.h"

/**
 * create_child - creates child process
 * @args: null terminated array of arguments to pass to execve
 * @argv: the first argument (name of the program) passed to main (argv[0])
 *
 * Return: exit value to use in main.
 */
int create_child(char **args, char *argv)
{
	pid_t child_pr;
	int status;

	child_pr = fork();

	if (child_pr == -1) /* error forking */
	{
		free(args[0]);
		free(args);
		perror("Error forking child process");
		exit(EXIT_FAILURE);
	}
	else if (child_pr == 0) /* child process */
	{
		if (execve(args[0], args, environ) == -1)
		{
			/*printf("%s: Not found\n", args[0]);*/
			free(args[0]);
			free(args);
			perror(argv);
			return (2);
		}
	}
	else /* parent process */
	{
		waitpid(child_pr, &status, 0); /* wait for child process to finish */
		return (exit_value(status));
	}

	return (0);
}
