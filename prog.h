#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define START_IC 100
#define MAX_ROW 82
#define MAX_LABEL 33


typedef struct {
		char *name;
		int funct;
		int code;
               } action;

typedef struct node{
                  int  count;
                  char *name;
                  int action;//to know what type, entry/extern
                  struct node *next;
                  }label;
typedef int word; 
typedef struct dNode{//the list of Directive sentences
		 int count;
		 word w1;
		 struct dNode *next;
		 } directive;
typedef char binaryWord[25]; 
typedef struct cNode{//the list of command sentences
		 int count;//the current IC value
		 binaryWord w1;
		 struct cNode *next;
		 } commands;

int checkFile(FILE *fileName);
int checkFile2(FILE *fileName);
int checkRow(char *row);
void checkRow2(char *row);
void outputFiles(char *fileName);
int skipSpace(char* row, int i);
int checkFirstParam(char *row, int i);
int isLabel(char *word);
int checkCommand(char *row, int i, int command);
int getNextWord(char *row, int i, char *word);
int commandIndex(char *word);
void creatActionTable();
int isValid(char *labelName);
int  labelM(char *name, int command);
int checkData(char * row,int i);
int checkString(char * row,int i);
int checkEntryExtern(char * row,int i);
int checkExtern(char * row,int i);
int getNextNum(char *row, int i);
int getNumber(char *row,int i);
int checkTwoParam(char *row,int i,int command);
int checkOneParam(char *row,int  i,int  command);
int checkZeroParam(char *row,int  i,int  command);
void createWord(binaryWord newWord, int command, int m1, int param1, int m2, int param2);
void addNodeC(int command, int m1, int param1, int m2, int param2);
char *changeBinary(int x, int size);
char* negetiveNum(char *binary, int size);
void printHex(binaryWord w1);

int IC;
int DC;
int ROW_NUM;//***
action actionTable[16];

