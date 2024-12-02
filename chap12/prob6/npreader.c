#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "/tmp/myfifo";
    char buffer[128];

    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    close(fd);

    printf("Message received from FIFO: %s\n", buffer);

    return 0;
}

