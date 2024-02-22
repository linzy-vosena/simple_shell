#include "shell.h"

/**
 * term_log - writes the character c to stdout
 * @c : the character to print
 *
 * Return: 0 (Success)
 * On error, -1 is returned, and errno is set appropriately
 */

char term_log(const char *c)
{
write(STDOUT_FILENO, c, strlen(c));
return (0);
}
