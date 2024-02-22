#include "shell.h"

char line[1024];

int main(){
  while (1) {
    term_log(PROMPT);
    term_log(" ");

    if (fgets(line, sizeof(line), stdin) == NULL) {
        term_log("\n");
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
