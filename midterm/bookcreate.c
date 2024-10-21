#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "db.dat"

int main(int argc, char *argv[])
{
   int fd;
   struct student record;
   if (argc < 2) {
      fprintf(stderr, "How to use: %s file\n", argv[0]);
      exit(1);
   }
      if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   printf("--bookquery--\n0 : list of all books, 1: list of available books ) %d \n", available books);
   printf("%-4s %-4s %-4s %-4s %-10s %-6s\n", "iD","bookname", "author", "year", "numofborrow", "borrow");
   while (scanf("%d %s %s %d %d %s", &record.id, record.bookname, &record.author, &record.year, &record.numofborrow, &record.borrow) == 6) {
      lseek(fd, (record.id - START_iD) * sizeof(record), SEEK_SET);
      write(fd, (char *) &record, sizeof(record) );
   }
   close(fd);
   exit(0);
}


