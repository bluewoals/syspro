#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

main()
{
	int len;
	int max;
	char words[5][MAXLINE];
	char temp[MAXLINE];
	max = 0;

	for(int i = 0; i < 5; i++) {
		// scanf("%s", words[i]);
		gets(line);
		copy(line, words[i]);
	}
	
	for(int i = 0; i < 5 - 1; i++) {
		for(int j = 0; j < 5 - 1 - i; j++) {
			if(strlen(words[j]) < strlen(words[j + 1])) {
				copy(words[j], temp);
				copy(words[j + 1], words[j]);
				copy(temp, words[j + 1]);
			}	
		}
	}

	for(int i = 0; i < 5; i++) 
		printf("%s\n", words[i]);
	
//    if(max > 0)
//		printf("%s \n%s \n %s \n %s \n %s \n", longest,  );

	return 0;
}

