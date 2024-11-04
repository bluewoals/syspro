#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void print_usage() {
    printf("Usage: ./main [-eENV_NAME] [-u] [-g] [-i] [-p]\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-e", 2) == 0) {
            char *env_name = argv[i] + 2;
            if (strlen(env_name) > 0) {
                char *env_value = getenv(env_name);
                if (env_value) {
                    printf("%s: %s\n", env_name, env_value);
                } else {
                    printf("Environment variable %s does not exist.\n", env_name);
                }
            } else {
                printf("All environment variables:\n");
                extern char **environ;
                for (char **env = environ; *env != NULL; env++) {
                    printf("%s\n", *env);
                }
            }
        } else if (strcmp(argv[i], "-u") == 0) {
            printf("Real user ID: %d, Effective user ID: %d\n", getuid(), geteuid());
        } else if (strcmp(argv[i], "-g") == 0) {
            printf("Real group ID: %d, Effective group ID: %d\n", getgid(), getegid());
        } else if (strcmp(argv[i], "-i") == 0) {
            printf("Process ID: %d\n", getpid());
        } else if (strcmp(argv[i], "-p") == 0) {
            printf("Parent process ID: %d\n", getppid());
        } else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    return 0;
}

