#ifndef proj4base_h
#define proj4base_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef enum STATUS {FALSE = 0, TRUE, NO = 0, YES} boolean;
typedef enum {waiting = 0, called = 1} STATUS;

int debugMode;


typedef struct grouspInfo
{
   char *name;
   int size;
   STATUS status;
}group;


typedef struct NODE
{
   group g1;
   struct NODE *pNext;
}Node;

typedef Node *groupPointer;


/* forward definition of functions */
int getNextNWSChar ();
int getPosInt ();
char *getName();
void clearToEoln();
void printCommands();
void doAdd (groupPointer *pHead, int debugMode);
void doCallAhead (groupPointer *pHead, int debugMode);
void doWaiting (groupPointer pHead, int debugMode);
void doRetrieve (groupPointer *pHead, int debugMode);
void doList (groupPointer pHead, int debugMode);
void doDisplay (groupPointer pHead);
void addToList(groupPointer *pHead, char *name, int size, STATUS status);
int doesNameExist(groupPointer pHead, char *name);
int updateStatus(groupPointer pHead, char *name, int debugMode);
char *retrieveAndRemove(groupPointer *pHead, int size, int debugMode);
int countGroupsAhead(groupPointer pHead, char *name, int debugMode);
void displayGroupSizeAhead(groupPointer pHead, char *name);
void displayListInformation(groupPointer pTemp);


#endif /* proj4base_h */
