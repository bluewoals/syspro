#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100

int main() {
    int pipefd[2];
    pid_t pid;
    char msg[MSG_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        close(pipefd[0]);
        sprintf(msg, "Hello from PID %d", getpid());
        printf("Send: [%d] %s\n", getpid(), msg);
        write(pipefd[1], msg, strlen(msg) + 1);
        close(pipefd[1]);
        wait(NULL);
    } else {
        close(pipefd[1]);
        read(pipefd[0], msg, MSG_SIZE);
        printf("Recv: [%d] %s\n", getpid(), msg);
        close(pipefd[0]);
        exit(0);
    }

    return 0;
}

