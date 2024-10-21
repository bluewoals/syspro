#include <stdio.h>

int main(int argc, char *argv[])
{
   char c;
   FILE *fp1, *fp2;
   if (argc !=3) {
      fprintf(stderr, "How to use: %s\n", argv[0]);
      return 1;
   }
   fp1 = fopen(argv[1], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }

   fp2 = fopen(argv[2], "w");
   while ((c = fgetc(fp1)) != EOF){
	   if (fp1  >= 'A' && fp1  <= 'Z') {
           fp1 += 32;
        }
        else if (fp1 >= 'a' && fp2 <= 'z') {
           fp1 -= 32;
        }
      fputc(c, fp2);

   fclose(fp1);
   fclose(fp2);
   return 0;
   }
}


