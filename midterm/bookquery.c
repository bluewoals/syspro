#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "db.dat"

int main(int argc, char *argv[])
{
   int fd, id;
   char c; 
   struct student record;
   if (argc < 2) {
      fprintf(stderr,"How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   do {
      if (scanf("%d",  &id) == 1) {
         lseek(fd, (id-START_iD)*sizeof(record), SEEK_SET);
          if ((read(fd, (char *) &record, sizeof(record)) > 0))
       printf("id:%d\t bookname:%d\t author:%s year:%d numofborrow:%d borrow:%s\n", record.id, record.bookname, record.author, record.year, record.numofborrow, record.borrow);
         else printf("Record %d Null\n", id);
      } 
	  close(fd);
	  exit(0);
   }
}


