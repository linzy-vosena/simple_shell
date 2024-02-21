#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "user$"

int main(){
  char line[1024];
  char *args[64];
  pid_t x; //child process ID
  int status;

  while (1) {
    printf(PROMPT);
    printf(" ");

    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\n");
        break;
    }

    char *token = strtok(line, "\n");
    int i = 0;
    do {
        args[i] = token;
        i++;
        token = strtok(NULL, "\n");
    } while (token != NULL);
 

    args[i] = NULL;

    if (i == 0)
      continue;

    x = fork();
    if (x == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (x == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(x, &status, 0);
    }
}

return 0;
}
