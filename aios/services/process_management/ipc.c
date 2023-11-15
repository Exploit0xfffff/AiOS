#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE 4096 // 4KB shared memory size

int main() {
    int shm_fd;
    void *ptr;
    const char *message = "Hello from Process 1!";

    // Create or open the shared memory object
    shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory object
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Memory map the shared memory object
    ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write a message to the shared memory
    sprintf(ptr, "%s", message);
    printf("Message written to shared memory: %s\n", (char *)ptr);

    // Wait a bit for another process to read from shared memory
    sleep(5);

    // Unmap the shared memory
    if (munmap(ptr, SHARED_MEMORY_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close the shared memory object
    if (close(shm_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory object (uncomment to remove)
    // if (shm_unlink(SHARED_MEMORY_NAME) == -1) {
    //     perror("shm_unlink");
    //     exit(EXIT_FAILURE);
    // }

    return 0;
}
