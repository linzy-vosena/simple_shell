#include "shell.h"

/**
 * chagedir - changes directory
 * @args: cd command, its arguments and/or options
 * @argv: name of this program's executable file
 *
 * Return: 0
 */
int chagedir(char **args, __attribute__((unused))char *argv)
{
	char cwd[TOKEN_BUFSIZE];
	int val = -1;

	if (strcmp(args[0], "cd") != 0)
		return (0);

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		val = chdir(getenv("HOME"));
	}
	else if (strcmp(args[1], "-") == 0)
	{
		val = chdir(getenv("OLDPWD"));
	}
	else
	{
		val = chdir(args[1]);
	}

	if (val == -1)
	{
		fprintf(stderr, "%s: 1: %s: can't cd to %s\n", argv, args[0], args[1]);
		/**
		 *fprintf(stderr, "%s: cd: can't cd to %s: %s\n", argv, new_dir,
		 *strerror(errno));
		 */
		return (val);
	}
	else if (val != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1); /* update env variable */
		/*printf("%s\n", cwd);*/
		setenv("PWD", cwd, 1);
	}
	return (0);
}


