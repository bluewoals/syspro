#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

void read_file(const char *filename, char lines[MAX_LINES][MAX_LINE_LENGTH], int *line_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open file");
        exit(1);
    }

    *line_count = 0;
    while (fgets(lines[*line_count], MAX_LINE_LENGTH, file) && *line_count < MAX_LINES) {
        (*line_count)++;
    }

    fclose(file);
}

void print_lines(char lines[MAX_LINES][MAX_LINE_LENGTH], int line_count, char *input) {
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < line_count; i++) {
            printf("%s", lines[i]);
        }
        return;
    }

    char *token = strtok(input, ",");
    while (token) {
        if (strchr(token, '-')) {
            int start, end;
            sscanf(token, "%d-%d", &start, &end);
            for (int i = start; i <= end && i <= line_count; i++) {
                printf("%s", lines[i - 1]);
            }
        } else {
            int line_number;
            sscanf(token, "%d", &line_number);
            if (line_number > 0 && line_number <= line_count) {
                printf("%s", lines[line_number - 1]);
            }
        }
        token = strtok(NULL, ",");
    }
}

int main(int argc, char *argv[]) {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int line_count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    read_file(filename, lines, &line_count);

    printf("File read success\nTotal line : %d\nyou can choose 1 ~ %d Line\nPls 'Enter' the line to select : ", line_count, line_count);

    char input[100];

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

     if (strcmp(input, "exit") != 0) {
         print_lines(lines, line_count, input);
     }

     return 0;
}

