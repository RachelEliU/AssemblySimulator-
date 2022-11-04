#include "prog.h"

//second pass over file
int checkFile2(FILE *fd1)
{
     ROW_NUM = 0;
     int flag = 0;//to check if a row has an error
     char row[100];
     fgets(row,100,fd1);//gets a whole row
     while(!feof(fd1))
     {
	checkRow2(row);//deals with each rows commands
        fgets(row,100,fd1);//gets the next whole row
     }
     //we finished going over this file input second time
     if(flag)//we found errors during second pass
        return 0;
     return 1;
}

void checkRow2(char *row)
{
     printf("\nIM CHECK ROW2 FOR %s",row);
}
extern directive *headD;
extern commands *headC;
void outputFiles(char *fileName)
{
directive *p;
commands *q;
p = headD;
q = headC;
while(p){
printf("\nDC: %07d\tword: %06x\n",p->count,p->w1);
p = p->next;
}

while(q){
printf("\nIC: %07d\t%s\t", q->count, q->w1);
printHex(q->w1);
q = q->next;
}
     printf("\nIM OUTPUT FOR %s\n",fileName);
}

void printHex(binaryWord w1)
{
int i,j,sum=0;
	for(i=0; i<6; i++)//six digits
	{
	  for(j=i*4; j<4*i+4; j++)
	    sum += (w1[j]=='0')? 0 : pow(2,3-j%4);
	 printf("%x", sum);
	 sum=0;
	}
}
