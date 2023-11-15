#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Run e2fsck on the specified filesystem (replace /dev/sdXN with your target)
        execlp("e2fsck", "e2fsck", "/dev/sdXN", NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("e2fsck exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("e2fsck did not exit properly\n");
        }
    }

    return 0;
}
