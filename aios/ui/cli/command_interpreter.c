#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

// Function to parse user input into command and arguments
void parse_input(char *input, char *command, char **args) {
    char *token;
    int arg_count = 0;

    token = strtok(input, " \n");
    while (token != NULL) {
        if (arg_count == 0) {
            strcpy(command, token);
        }
        args[arg_count++] = token;
        token = strtok(NULL, " \n");
    }
    args[arg_count] = NULL;
}

// Function to execute commands
void execute_command(char *command, char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        if (execvp(command, args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        wait(NULL); // Wait for the child process to complete
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        printf("Command> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        // Exit if "exit" command is entered
        if (strcmp(input, "exit") == 0) {
            break;
        }

        parse_input(input, command, args);

        execute_command(command, args);
    }

    return 0;
}
