#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
  
int main()
{
        int P0, P1, P2, P3, P4, P5, P6, P7;
 
        P0 = fork();
        if(P0 == 0) {
			printf("Hello\n");
			exit(0);
        }

		P1 = fork();
		if(P1 == 0) {
			printf("Hello\n");
		}
		if(P3 == 0) {
			printf("Hello\n");
		}
		if(P7 == 0) {
			printf("Hello\n");
			exit(1);
		}
		if(P6 == 0) {
			printf("Hello\n");
			exit(2);
		}
		
		P4 = fork();
		if(P4 == 0) {
			printf("Hello\n");
			exit(3);
		}

		P2 = fork();
		if(P2 == 0) {
			printf("Hello\n");
		}
		if(P5 == 0) {
			printf("Hello\n");
			exit(4);
		}
}


