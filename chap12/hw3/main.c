#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    char str[1024];
    char *command1, *command2;
    char *args1[100], *args2[100];
    int fd[2];

    if (argc > 1) {
        strcpy(str, argv[1]);
    } else {
        printf("[shell]");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';
    }

    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "|");
        command2 = strtok(NULL, "|");
    }

    pipe(fd);

    if (fork() == 0) {
        close(fd[READ]);
        int i = 0;
        args1[i] = strtok(command1, " ");
        while (args1[i] != NULL) {
            i++;
            args1[i] = strtok(NULL, " ");
        }
        dup2(fd[WRITE], 1);
        close(fd[WRITE]);
        execvp(args1[0], args1);
        perror("pipe");
        exit(1);
    } else {
        close(fd[WRITE]);
        int i = 0;
        args2[i] = strtok(command2, " ");
        while (args2[i] != NULL) {
            i++;
            args2[i] = strtok(NULL, " ");
        }
        dup2(fd[READ], 0);
        close(fd[READ]);
        execvp(args2[0], args2);
        perror("pipe");
        exit(1);
    }

    return 0;
}

