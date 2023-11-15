#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;

    // Allocate memory for 5 integers
    ptr = (int *)malloc(5 * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize and display the allocated memory
    for (int i = 0; i < 5; i++) {
        ptr[i] = i + 1;
        printf("Value at index %d: %d\n", i, ptr[i]);
    }

    // Deallocate the allocated memory
    free(ptr);

    return 0;
}
