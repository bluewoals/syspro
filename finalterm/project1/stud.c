#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
  
   int main()
   {
      int pid1, pid2, child, status;

	  printf("type num of childs : ");
	  scanf("%d", &child);
      pid1 = fork();
      if(pid1 == 0) {
          printf("[Child 0] : Started! pid=%d, sleep=1\n", getpid());
          sleep(1);
		  printf("[Child 2] : Started! pid=%d, sleep=3\n", getpid());
		  sleep(2);
		  printf("[Child 1] : Killed! pid=%d, sleep=2\n", getpid());
		  sleep(3);
		  exit(1);
      }
 
      pid2 = fork();
      if(pid2 == 0){
		  printf("[Child 1] : Started! pid=%d, sleep=2\n", getpid());
          sleep(1);
		  printf("[Child 0] : Killed! pid=%d, sleep=1\n", getpid());
          sleep(2);
          printf("[Child 2] : Killed! pid=%d, sleep=3\n", getpid());
		  sleep(3);
          exit(2);
      }

   child = waitpid(pid1, &status, 0);
   printf("parent killed - last child id = %d\n", getpid());
  }

