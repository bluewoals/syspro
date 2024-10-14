#include <stdio.h>
#include <stdlib.h>

void appendFile(const char *sourceFile, const char *destinationFile) {
    FILE *src, *dest;
    char buffer[1024];

    src = fopen(sourceFile, "r");
    if (src == NULL) {
        perror("Cannot open source file");
        exit(EXIT_FAILURE);
    }

    dest = fopen(destinationFile, "a");
    if (dest == NULL) {
        perror("Cannot open destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), src) != NULL) {
        fputs(buffer, dest);
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    appendFile(argv[1], argv[2]);
    printf("Contents of '%s' appended to '%s'.\n", argv[1], argv[2]);

    return EXIT_SUCCESS;
}

