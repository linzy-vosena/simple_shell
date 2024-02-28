#include "shell.h"

/**
 * exit_value - deals with different exit status codes from child process
 * @status: status exit code of child retrieved from system by waitpid
 *
 * Return: void
 */
int exit_value(int status)
{
	int exit_status;
	int signal_number;

	if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		if (signal_number == SIGSEGV)
		{	/* handle segmentation fault */
			/*exit(signal_number);*/
		}
		else if (signal_number == SIGTERM)
		{	/* handle termination by user */
			/*exit(signal_number);*/
		}
		else if (signal_number == SIGINT)
		{	/* child process was interrupted by Ctrl+C */
			/*exit(signal_number);*/
		}
	}
	/*else if (WIFEXITED(status))*/
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status == 0)
		{	/* child process exited successfully */
			return (0);
		}
		else if (exit_status == 2)
		{	/* handle non-zero exit status */
			return (2);
		}
		else if (exit_status == 127)
			return (127);
	}
	return (127);
}


