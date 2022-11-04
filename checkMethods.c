#include "prog.h"

//just for now

int checkMov(char * row,int i){return 1;}
int checkCmp(char * row,int i){return 1;}
int checkAdd(char * row,int i){return 1;}
int checkSub(char * row,int i){return 1;}
int checkLea(char * row,int i){return 1;}
int checkClr(char * row,int i){return 1;}
int checkNot(char * row,int i){return 1;}
int checkInc(char * row,int i){return 1;}
int checkDec(char * row,int i){return 1;}
int checkJmp(char * row,int i){return 1;}
int checkBne(char * row,int i){return 1;}
int checkJsr(char * row,int i){return 1;}
int checkRed(char * row,int i){return 1;}
int checkPrn(char * row,int i){return 1;}
int checkRts(char * row,int i){return 1;}
int checkStop(char * row,int i){return 1;}



//checks first thing in row after spaces
int checkFirstParam(char *row, int i)
{
    int j, command;
    char word[MAX_LABEL], *temp="";
    if (i == MAX_ROW || row[i] == ';')
         return 1; //empty row or note, compiler ignores
    i = getNextWord(row,i,word);//gets first word
    if(isLabel(word))
     {
	 temp = (char *) malloc(sizeof(word-1));//we will save the label here
	 if(!temp)
	 {
	   printf("\nmalloc error\n");
	   exit(0);
	 }
         strncpy(temp, word,strlen(word+1));//copy the label name without ':'
         if((i=skipSpace(row,i)) == MAX_ROW)
         {
            printf("\nIn row %d: missing text after label\n",ROW_NUM);
            return 0;
         }  
         i = getNextWord(row, i, word);
     }
     command = commandIndex(word);//index of command in the command table
     if(command == -1)//invalid command index
            return 0;
     if(strcmp(temp, ""))//is label  ****
       if(!labelM(temp, command))//this function deals with the label
            return 0;
    return checkCommand(row, i, command);//deals with rest of row according to the current input command
}

int getNextWord(char *row, int i, char *word)
{
    int j;
    for(j=0; j<MAX_LABEL-1; j++)//save first word this should be a private function...
     {
        if(row[i+j] == ' ' || row[i+j] == '\t' || row[i+j] == '\n')
         {
           word[j] = '\0';//end of first word
           break;
         }
        word[j] = row[i+j];
     }
    if(j==32)
       word[j] = '\0';
    return i+j;
}

int isLabel(char *word)
{
    int i = 0;
    if(!isalpha(word[0]))
       return 0;
    while(word[i] != '\0')
     {
      if((!isalnum(word[i]) && word[i]!= ':') || (word[i] == ':' && i<32 && word[i+1] != '\0'))
            return 0;
      if(word[i] == ':')
            return 1;//is label
      i++;
     }
    return 0; //no : at the end
}

int commandIndex(char *word)
{
    int i;
    for(i=0; i<16; i++)
       if(!strcmp(actionTable[i].name,word))
            return i;
    //not command
    if(!(strcmp(".data",word)))//משפט הנחיה
            return 16;
    if(!(strcmp(".string",word)))
            return 17;
    if(!(strcmp(".entry",word)))
            return 18;
    if(!(strcmp(".extern",word)))
            return 19;
    printf("In row %d: The action %s does not exist\n",ROW_NUM,word);
    return -1;
}

label *head = NULL;//maybe static
int  labelM(char *name, int command)//function that deals with valid label if .extern command=2000 or so...
{  
   label *newNode;
   if(!isValid(name))//check if label already axists or same as command name or not valid, prints a matching error message
        return 0;
   if(command >17)
   {
	printf("WARNING: In row %d: invalid command %s after label\n",ROW_NUM,(command==18)? ".entry" : ".extern");
        return 1;
   }
   newNode = (label *) malloc(sizeof(label));
   if(!newNode)
   {
      printf("\nmalloc error- cannot built list\n");
      exit(0);
   }
   //the label is valid. add to list
   newNode->count = (command<16)? IC : DC;
   newNode->name = name;
   newNode->action = command;
   newNode->next = head;//נוסיף כל פעם לראש הרשימה, ובסוף כדי לקבל סדר נכון ניעזר ברקורסיה...
   head = newNode;//point to the head of list each time
   return 1;
}

int isValid(char *labelName)
{
   int i;
   label *p = head;
   while(p)
   {
     if(!strcmp(p->name, labelName))
        {
         printf("In row %d: The label \"%s\" already exists\n",ROW_NUM,labelName);
         return 0;
        }
     p = p->next;
   }
   for(i=0;i<16;i++)
	if(!strcmp(labelName, actionTable[i].name))
	{
	   printf("In row %d: invaid label name. The label \"%s\" has same name as command\n",ROW_NUM,labelName);
	   return 0;
	}
   return 1;
}


/*this function gets a string representing the input command, analyzes it,  calls and returns the proper method, 
  if the commans is undefined- prints a matching error and returns 1 to continue to the next row*/
int checkCommand(char *row, int i, int command)
{
        i = skipSpace(row,i);
	switch(command){
           case 0: case 1: case 2: case 3: case 4: 
                return checkTwoParam(row, i, command);
           case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: 
                return checkOneParam(row, i, command);
           case 14: case 15: 
                return checkZeroParam(row, i, command);
           case 16: 
                return checkData(row, i);
           case 17:
		return checkString(row, i);
           case 18: case 19: 
		return checkEntryExtern(row, i);
           default:
                printf("\nerror\n");//not suppost to get here, just incase
                return 0;
             }
  }
       
       /*if(!(strcmp("mov",word)))
            return checkMov(row, i);
       if(!(strcmp("cmp",word)))
            return checkCmp(row, i);
       if(!(strcmp("add",word)))
            return checkAdd(row, i);
       if(!(strcmp("sub",word)))
            return checkSub(row, i);
       if(!(strcmp("lea",word)))
            return checkLea(row, i);
       if(!(strcmp("clr",word)))//*
            return checkClr(row, i);
       if(!(strcmp("not",word)))
            return checkNot(row, i);
       if(!(strcmp("inc",word)))
            return checkInc(row, i);
       if(!(strcmp("dec",word)))
            return checkDec(row, i);
       if(!(strcmp("jmp",word)))
            return checkJmp(row, i);
       if(!(strcmp("bne",word)))
            return checkBne(row, i);
       if(!(strcmp("jsr",word)))
            return checkJsr(row, i);
       if(!(strcmp("red",word)))
            return checkRed(row, i);
       if(!(strcmp("prn",word)))
            return checkPrn(row, i);
       if(!(strcmp("rts",word)))//0 operands
            return checkRts(row, i);
       if(!(strcmp("stop",word)))
            return checkStop(row, i);*/

