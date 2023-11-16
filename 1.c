#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        display_prompt();

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break; // End of file (Ctrl+D) or error
        }

        // Remove the newline character from the command
        size_t length = strlen(command);
        if (command[length - 1] == '\n') {
            command[length - 1] = '\0';
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            execlp(command, command, (char *)NULL);
            
            // If execlp fails
            perror(command);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            // Check if the child process terminated successfully
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: %s: command not found\n", command);
            }
        }
    }

    return 0;
}

