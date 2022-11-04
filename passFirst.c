#include "prog.h"
extern label *head;
//goes through each file and deals with it
int checkFile(FILE *fd1)//***מעבר ראשון בודק את כל אפשרויות השגיאה, כולל מספר הפרמטרים
{
     ROW_NUM = 0;
     int flag = 0;//to check if a row has an error
     char row[MAX_ROW];//will contain a whole row of the input
     fgets(row,MAX_ROW,fd1);//gets a whole row
     while(!feof(fd1))
     {
        ROW_NUM++;
	if(!checkRow(row))//deals with each row first time, check row returns zero if there was an error
           flag = 1;
        fgets(row,MAX_ROW,fd1);//gets the next whole row
     }
     //we finished going over this file input once
     if(flag)//there was an error
     {
        printf("\n*****************\n");//***
        return 0;
     }
     rewind(fd1);
     return checkFile2(fd1);//going over this file input second time from the beginning
}

int checkRow(char *row)
{
     printf("\nIM CHECK ROW1 FOR %s",row);//***
     return checkFirstParam(row,skipSpace(row,0));//check all options.... if label:, if command, if .data etc., .entry... 
}

int skipSpace(char* row, int i)//***לבדוק מקרי קצה....
{
     while(i<MAX_ROW && (row[i]==' '||row[i]=='\t'))//skip space
         i++;
     return (row[i] == '\0' || row[i] == EOF || row[i] == '\n')? MAX_ROW : i;//the index where the next character is, if end of row return 100
}
