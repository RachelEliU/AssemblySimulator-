#include "prog.h"

/*this function checks in first pass if the command rows starting with .extern/.entry are valid*/
int checkEntryExtern(char * row,int i)
{
	char word[MAX_LABEL];/*for getting the next word, expected label*/
	int j;
	i = getNextWord(row, i, word);
	if(!isalpha(word[0]) || (i=skipSpace(row,i)) != MAX_ROW )
	{
	   printf("\nIn row %d: wrong text after command, only label expected\n",ROW_NUM);
           return 0;
        }
       

	for(j=0;j<16;j++)
	  if(!strcmp(word, actionTable[j].name))
	  {
	     printf("In row %d: wrong text after command, only label expected (invaid label name).\n",ROW_NUM);
	     return 0;
	  }
	return 1;
}


directive *headD = NULL, *lastD=NULL;
int checkString(char *row, int i) 
{
	directive *newNode;
	int j, temp;
	if(i == MAX_ROW || row[i] != '\"')
	{
	   printf("\nIn row %d: wrong format for string, expected quotation marks\n",ROW_NUM);
           return 0;
        }
        if((j = strrchr(row,'\"') - row) == i)
	{
	   printf("\nIn row %d: wrong text for string, expected closing quotation marks\n",ROW_NUM);
           return 0;
        }
	if((temp = skipSpace(row,j+1)) != MAX_ROW)
	{
	   printf("\nIn row %d: extra text after string\n",ROW_NUM);
           return 0;
        }
        for(i=i+1; i<=j; i++)
	{
           newNode = (directive *) malloc(sizeof(directive));
	   if(!newNode)
  	   {
  	      printf("\nmalloc error- cannot built directive list\n");
              exit(0);
  	   }  
	   newNode->count = DC++;
	   newNode->w1 = (i==j)? 0 : row[i];
	   newNode->next = NULL;
           if(headD == NULL)
	   {
              headD = newNode;
	      lastD = newNode;
	   }
           else
           {
	      lastD->next = newNode;
	      lastD = newNode;
           }
	}
        return 1;
}

int checkData(char *row, int i)
{
	directive *newNode;
	int j;
	if(i == MAX_ROW)
	{
	   printf("\nIn row %d: wrong format for data, expected natural number1\n",ROW_NUM);
           return 0;
        }
	if((j = getNextNum(row,i)) == -1)
	   return 0;
        while(j!=MAX_ROW)//not end of row
	{
           if(row[j] != ',')
	   {
	      printf("\nIn row %d: wrong format for data, expected comma\n",ROW_NUM);
              return 0;
           }
           j = skipSpace(row,j+1);
	   if((j = getNextNum(row,j)) == -1)
              return 0;
	}
	while (i < MAX_ROW) 
	{
	   newNode = (directive *) malloc(sizeof(directive));
	   if(!newNode)
  	   {
  	      printf("\nmalloc error- cannot built directive list\n");
              exit(0);
  	   }  
	   newNode->count = DC++;
	   newNode->w1 = getNumber(row, i);
	   newNode->next = NULL;
           if(headD == NULL)
	   {
              headD = newNode;
	      lastD = newNode;
	   }
           else
           {
	      lastD->next = newNode;
	      lastD = newNode;
           }
	i = getNextNum(row,i);//skip current number
	i = skipSpace(row,i+1);//skip comma
}
        //create word for each number with new function
        return 1;
}
int getNextNum(char *row, int i)
{
	int counter = 0;
	if(row[i] == '+' || row[i] == '-')
	   i++;
	while(i<MAX_ROW && isdigit(row[i]))
	{
	   counter++;
	   i++;
	}
	if(counter == 0 || (row[i]!='\n' && row[i]!=',' && row[i]!='\t' && row[i]!=' ' && row[i]!=EOF))//no number or wrong text after number
	{
	   printf("\nIn row %d: wrong format for data, expected natural number3\n",ROW_NUM);
           return -1;
        }
	return skipSpace(row,i);
}

int getNumber(char *row,int i)
{
	int j = 0;
	char s[MAX_ROW];
	while(row[i] == '+' || row[i] == '-' || isdigit(row[i]))//the numbers are already currect
	   s[j++] = row[i++];//save current number
	s[j] = '\0';
	return atoi(s);//the string as an integer
}
