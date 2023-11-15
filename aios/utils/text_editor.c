#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TEXT_LENGTH 1000

int main() {
    char text[MAX_TEXT_LENGTH];
    printf("Simple Text Editor\n");
    printf("Enter text (type 'exit' to quit):\n");

    while (1) {
        fgets(text, sizeof(text), stdin);

        // Check for 'exit' command to quit the text editor
        if (strcmp(text, "exit\n") == 0) {
            break;
        }

        // Print the entered text
        printf("Entered text: %s", text);
    }

    printf("Exiting the text editor.\n");

    return 0;
}
