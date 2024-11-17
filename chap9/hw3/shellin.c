#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    char *input_file = NULL, *output_file = NULL;
    int background = 0;
    int in_fd = -1, out_fd = -1;
    char *token;

    if (strchr(cmd, '&')) {
        background = 1;
        strtok(cmd, "&");
    }

    token = strtok(cmd, " \t\n");
    int arg_index = 0;
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            output_file = strtok(NULL, " \t\n");
        } else if (strcmp(token, "<") == 0) {
            input_file = strtok(NULL, " \t\n");
        } else {
            args[arg_index++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[arg_index] = NULL;

    if (input_file) {
        in_fd = open(input_file, O_RDONLY);
        if (in_fd == -1) {
            perror("input file");
            return;
        }
        dup2(in_fd, STDIN_FILENO);
    }
    if (output_file) {
        out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("output file");
            return;
        }
        dup2(out_fd, STDOUT_FILENO);
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(1);
        }
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    } else {
        perror("fork");
    }

    if (in_fd != -1) close(in_fd);
    if (out_fd != -1) close(out_fd);
}

void process_input(char *input) {
    char *cmd = strtok(input, ";");
    while (cmd != NULL) {
        execute_command(cmd);
        cmd = strtok(NULL, ";");
    }
}

int main() {
    char input[MAX_CMD_LENGTH];

    while (1) {
        printf("[shell] ");
        if (fgets(input, MAX_CMD_LENGTH, stdin) == NULL) {
            break;
        }
        if (input[0] == '\n') {
            continue;
        }
        process_input(input);
    }

    return 0;
}
