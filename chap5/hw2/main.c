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

void print_lines_reverse(char lines[MAX_LINES][MAX_LINE_LENGTH], int line_count) {
    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
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

    print_lines_reverse(lines, line_count);

    return 0;
}

