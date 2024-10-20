#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int);
void printHumanReadableSize(off_t size);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int detailed = 0, show_hidden = 0, human_readable = 0;

    // Parse options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            detailed = 1;
        } else if (strcmp(argv[i], "-a") == 0) {
            show_hidden = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            human_readable = 1;
        } else {
            dir = argv[i];
        }
    }

    if (dir == NULL) {
        dir = ".";
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL) {
        if (!show_hidden && d->d_name[0] == '.') {
            continue; // Skip hidden files
        }

        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(path, d->d_name, &st, detailed, human_readable);
        }
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int detailed, int human_readable) {
    if (detailed) {
        printf("%5d ", st->st_blocks);
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
        if (human_readable) {
            printHumanReadableSize(st->st_size);
        } else {
            printf("%9d ", st->st_size);
        }
        printf("%.12s ", ctime(&st->st_mtime) + 4);
        printf("%s\n", file);
    } else {
        printf("%s\n", file); // Just print the file name
    }
}

void printHumanReadableSize(off_t size) {
    const char *sizes[] = {"B", "KB", "MB", "GB", "TB"};
    int order = 0;
    double value = size;

    while (value >= 1024 && order < (sizeof(sizes) / sizeof(sizes[0])) - 1) {
        order++;
        value /= 1024;
    }
    printf("%9.1f %s ", value, sizes[order]);
}

char type(mode_t mode) {
    if (S_ISREG(mode)) return '-';
    if (S_ISDIR(mode)) return 'd';
    if (S_ISCHR(mode)) return 'c';
    if (S_ISBLK(mode)) return 'b';
    if (S_ISLNK(mode)) return 'l';
    if (S_ISFIFO(mode)) return 'p';
    if (S_ISSOCK(mode)) return 's';
    return '?'; // Unknown file type
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3)) perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3)) perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3)) perms[i * 3 + 2] = 'x';
    }
    return perms;
}

