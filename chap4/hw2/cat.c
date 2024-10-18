#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(const char *filename, int line_numbering) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char buffer[1024];
    int line_number = 1;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (line_numbering) {
            printf("%6d  ", line_number++);
        }
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int line_numbering = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        line_numbering = 1;
        argv++;
        argc--;
    }

    if (argc < 2) {
        fprintf(stderr, "test\ntest\n", argv[0]);

        return 1;
    }
 
    for (int i = 1; i < argc; i++) {
         print_file(argv[i], line_numbering);
    }

         return 0;
}
