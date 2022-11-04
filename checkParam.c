#include "prog.h"

int checkTwoParam(char *row,int  i,int  command)
{
 	return 1;
}

int checkZeroParam(char *row,int  i,int  command)
{
	if(i != MAX_ROW)
	{
	   printf("In row %d: extra text after command",ROW_NUM);
	   return 0;
	}
	addNodeC(command,0,0,0,0);//reate word both params are 0
	return 1;
}

int checkOneParam(char *row,int  i,int  command)
{
//check if not labbel and uger
//erro
//if is uger
//else will get the word add : and check if its labbel
// 
	return 1;
}

commands *headC = NULL, *lastC=NULL;
/*this function creates a new binary word*/
void addNodeC(int command, int m1, int param1, int m2, int param2)
{
	commands *newNode;
	binaryWord newWord;
        newNode = (commands *)malloc(sizeof(commands));
	if(!newNode)
        {
           printf("\nmalloc error- cannot built command list\n");
           exit(0);
        }
        newNode->count = IC++;
	createWord(newNode->w1, command, m1, param1, m2, param2);
	newNode->next = NULL;
        if(headC == NULL)
	{
           headC = newNode;
	   lastC = newNode;
	}
        else
        {
	  lastC->next = newNode;
          lastC = newNode;
        }
}
//creates binary word, gets all data
void createWord(binaryWord newWord, int command, int m1, int param1, int m2, int param2)
{
	char *p;
	int i, j=0,k;
	p = changeBinary(command, 6);//inserts the command in binary to the word
	for(i=0; i<6; i++)
	   newWord[j++] = p[i];
	p = changeBinary(m1, 2);
	for(i=0; i<2; i++)
	   newWord[j++] = p[i];
	p = changeBinary(param1, 3);
	for(i=0; i<3; i++)
	   newWord[j++] = p[i];
	p = changeBinary(m2, 2);
	for(i=0; i<2; i++)
	   newWord[j++] = p[i];
	p = changeBinary(param2, 3);
	for(i=0; i<3; i++)
	   newWord[j++] = p[i];
	p = changeBinary(actionTable[command].funct, 5);
	for(i=0; i<5; i++)
	   newWord[j++] = p[i];
	newWord[j++] = '1';
	newWord[j++] = '0';
        newWord[j] = '0';
        newWord[24] = '\0';//end of binary word represented as string
}
/*this function gets a number and size in word, and returns a pointer to the number as binary*/
char *changeBinary(int x, int size)
{
	char *binary;
	int count = size-1, i = 0, isnegetive = 0;
	if(x<0)//the number is negetive
	{
	   x *= -1;//change the number to positive  
	   isnegetive = 1;
	}
        binary = (char *)malloc(size*sizeof(char));
	if(!binary)
        {
           printf("\nmalloc error- cannot built binary num\n");
           exit(0);
        }
	while(count >= 0)
	{
	   binary[count--] = (x % 2)? '1' : '0';
	   x /= 2;
	}
        if(isnegetive)//this number was negetive
   	   binary = negetiveNum(binary, size-1);
	return binary;
}

/*gets a pointer to an array representing a positive binary num and last index of array*/
char* negetiveNum(char *binary, int size)
{
	while(size >= 0 && binary[size] == '0')
	   size--;//skip all '0'
	size--;//skip first '1'
	while(size >= 0)//שיטת המשלים ל2
	   binary[size--] = (binary[size] == '0')? '1' : '0';//change all the west to the mashlim l2
	return binary;
}
