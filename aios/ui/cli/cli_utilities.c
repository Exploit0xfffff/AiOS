#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to copy a file
void copy_file(const char *source, const char *destination) {
    FILE *src, *dest;
    char buffer[BUFSIZ];
    size_t bytes_read;

    src = fopen(source, "rb");
    if (src == NULL) {
        perror("fopen source");
        return;
    }

    dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("fopen destination");
        fclose(src);
        return;
    }

    while ((bytes_read = fread(buffer, 1, BUFSIZ, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
}

// Function to list directory contents
void list_directory(const char *path) {
    #include <dirent.h>

    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

// Function to create a directory
void create_directory(const char *path) {
    if (mkdir(path, 0777) == -1) {
        perror("mkdir");
        return;
    }

    printf("Directory created successfully.\n");
}

int main() {
    const char *source_file = "source.txt";
    const char *destination_file = "destination.txt";
    const char *directory_path = "new_directory";

    // Copy a file
    copy_file(source_file, destination_file);

    // List directory contents
    list_directory(".");

    // Create a directory
    create_directory(directory_path);

    return 0;
}
