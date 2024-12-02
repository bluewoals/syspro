#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

int main() {
    int pipe1[2];
    pid_t pid1, pid2;
    char buffer[BUF_SIZE];

    if (pipe(pipe1) == -1) {
        perror("pipe1");
        exit(1);
    }

    printf("parent process start\n");

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork1");
        exit(1);
    }

    if (pid1 == 0) {
        close(pipe1[0]);
        printf("input string: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        write(pipe1[1], buffer, strlen(buffer) + 1);
        close(pipe1[1]);
        exit(0);
    } else {
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork2");
            exit(1);
        }

        if (pid2 == 0) {
            close(pipe1[1]);
            read(pipe1[0], buffer, BUF_SIZE);
            for (int i = 0; buffer[i] != '\0'; i++) {
                buffer[i] = toupper(buffer[i]);
            }
            printf("%s\n", buffer);
            close(pipe1[0]);
            exit(0);
        } else {
            wait(NULL);
            wait(NULL);
            exit(0);
        }
    }

    return 0;
}

