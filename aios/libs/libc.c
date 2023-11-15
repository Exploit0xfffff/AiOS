#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

// Example implementation of strlen() - string length function
size_t strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Example implementation of strcpy() - string copy function
char* strcpy(char *dest, const char *src) {
    char *start = dest;
    while ((*dest++ = *src++) != '\0');
    return start;
}

// Example implementation of atoi() - string to integer conversion
int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

int main() {
    // Example usage of functions from hypothetical libc
    const char *text = "Hello, World!";
    
    // Calculate the length of a string
    size_t length = strlen(text);
    printf("Length of '%s' is %zu\n", text, length);
    
    // Copy a string
    char copied[20];
    strcpy(copied, text);
    printf("Copied string: %s\n", copied);
    
    // Convert string to integer
    const char *number = "12345";
    int converted = atoi(number);
    printf("Converted number: %d\n", converted);
    
    return 0;
}
