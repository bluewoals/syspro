#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "/tmp/myfifo";
    char *message = "Hello, FIFO!";

    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    write(fd, message, sizeof(message));
    close(fd);

    printf("Message written to FIFO: %s\n", message);

    return 0;
}



