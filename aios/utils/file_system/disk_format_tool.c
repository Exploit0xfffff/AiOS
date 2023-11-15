#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

#define DEVICE_PATH "/dev/sdX" // Replace 'X' with the appropriate disk identifier

int main() {
    int fd;
    const char *device = DEVICE_PATH;

    // Open the device for read/write access
    fd = open(device, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Format the disk with a filesystem (e.g., EXT4)
    if (ioctl(fd, BLKFLSBUF, 0) == -1) {
        perror("ioctl BLKFLSBUF");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (ioctl(fd, BLKRRPART, 0) == -1) {
        perror("ioctl BLKRRPART");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (ioctl(fd, BLKDISCARD, 0) == -1) {
        perror("ioctl BLKDISCARD");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (ioctl(fd, BLKFLSBUF, 0) == -1) {
        perror("ioctl BLKFLSBUF");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Disk formatted successfully.\n");

    close(fd);

    return 0;
}
