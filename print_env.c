#include "shell.h"

/**
 * print_env - prints the environment
 * @args: the arguments and/or options to the command
 *
 * Return: void
 */
void print_env(char **args)
{
	size_t count, f;
	int length;
	char **env_ptrs; /* Array of pointers to strings */

	if (strcmp(args[0], "env") == 0)
	{
		/* count the number of env variables*/
		for (count = 0; environ[count] != NULL; count++)
			;

		env_ptrs = malloc(count * sizeof(char *));

		if (env_ptrs == NULL)
		{
			perror("print_env malloc error");
			exit(EXIT_FAILURE);
		}

		for (f = 0; f < count; f++)
			env_ptrs[f] = environ[f];

		/* sort the array of pointers */
		qsort(env_ptrs, count, sizeof(char *), compare_strings);

		/* print the sorted env variables */
		for (f = 0; f < count; f++)
		{
			if (!is_variable_to_exclude(env_ptrs[f]))
			{
				length = strlen(env_ptrs[f]);
				write(1, env_ptrs[f], length);
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		free(env_ptrs);
	}
}

/**
 * compare_strings - compares two strings using strcmp
 * @a: first string
 * @b: second string
 *
 * Return: result of comparison
 */
int compare_strings(const void *a, const void *b)
{
	return (strcmp(*(const char **)b, *(const char **)a));
}

/**
 * is_variable_to_exclude - checks if variable should be excluded from sorting
 * @variable: the environment variable to check
 *
 * Return: 1 for variable to exclude, 0 otherwise
 */
int is_variable_to_exclude(const char *variable)
{
	/* any variables that should be excluded from sorting are added here */
	const char *excluded_vars[] = {"LESSOPEN", "USER", "SHLVL", "WT_PROFILE_ID",
		"MOTD_SHOWN", "HOME", "OLDPWD", "WSL_DISTRO_NAME", "DEBUGINFOD_URLS",
		"LOGNAME", "NAME", "TERM", "PATH", "WT_SESSION", "LANG",
		"LS_COLORS", "SHELL", "LESSCLOSE", "PWD", "XDG_DATA_DIRS",
		"HOSTTYPE", "WSLENV", NULL};
	int f;

	for (f = 0; excluded_vars[f] != NULL; f++)
	{
		if (strcmp(variable, excluded_vars[f]) == 0)
			return (1); /* variable should be excluded */
	}
	return (0); /* variable shold not be excluded */
}



