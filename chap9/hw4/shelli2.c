#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXARG 100

void execute_command(char *input) {
    char *args[MAXARG];
    char *token;
    int background = 0;

    token = strtok(input, " \n\t");
    int i = 0;

    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            background = 1;
            break;
        }
        args[i++] = token;
        token = strtok(NULL, " \n\t");
    }
    args[i] = NULL;

    pid_t pid = fork();
    
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp 실패");
            exit(1);
        }
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    } else {
        perror("fork 실패");
        exit(1);
    }
}

int main() {
    char input[1024];

    while (1) {
        printf("[Shell] ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("입력 받기 실패");
            exit(1);
        }

        if (input[0] == '\n') {
            continue;
        }

        execute_command(input);
    }

    return 0;
}

