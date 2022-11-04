#include "prog.h"


int main(int argc, char *argv[])
{
     int i;
     char *fileName;
     FILE *fd1;//pointer to the current file
     creatActionTable();
     for(i=1; i<argc; i++)
     {
          IC = START_IC;
          DC = 0;
          if(!(fd1 = fopen(argv[i],"r")))//if the input file cannot be opened
             printf("The input file \"%s\" cannot be opened\n",argv[i]);
          else 
          {
             fileName = argv[i];
             if(checkFile(fd1)) /*deals with each input file*/
     	           outputFiles(fileName);//the file is currect and we will built the three output files
   	     fclose(fd1);//we are done with this file
          }
     }
     return 0;
}
