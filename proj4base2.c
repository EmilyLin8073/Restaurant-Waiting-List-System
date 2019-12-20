#include "proj4base.h"

void doAdd (groupPointer *pHead, int debugMode)
{
   /* get group size from input */
   int size = getPosInt();
   if (size < 1)
   {
      printf ("Error: Add command requires an integer value of at least 1\n");
      printf ("Add command is of form: a <size> <name>\n");
      printf ("  where: <size> is the size of the group making the reservation\n");
      printf ("         <name> is the name of the group making the reservation\n");
      return;
   }

   /* get group name from input */
   char *name = getName();
   if (NULL == name)
   {
      printf ("Error: Add command requires a name to be given\n");
      printf ("Add command is of form: a <size> <name>\n");
      printf ("  where: <size> is the size of the group making the reservation\n");
      printf ("         <name> is the name of the group making the reservation\n");
      return;
   }

   // add code to perform this operation here

   //check if the name already exists in the waitlist
   if(doesNameExist(*pHead, name))
   {
      printf("Name already exists in the wait list\n");
      return;
   }
   else
   {
      printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);
      addToList(pHead, name, size, waiting);
   }
}


void doCallAhead (groupPointer *pHead, int debugMode)
{
   /* get group size from input */
   int size = getPosInt();
   if (size < 1)
   {
      printf ("Error: Call-ahead command requires an integer value of at least 1\n");
      printf ("Call-ahead command is of form: c <size> <name>\n");
      printf ("  where: <size> is the size of the group making the reservation\n");
      printf ("         <name> is the name of the group making the reservation\n");
      return;
   }

   /* get group name from input */
   char *name = getName();
   if (NULL == name)
   {
      printf ("Error: Call-ahead command requires a name to be given\n");
      printf ("Call-ahead command is of form: c <size> <name>\n");
      printf ("  where: <size> is the size of the group making the reservation\n");
      printf ("         <name> is the name of the group making the reservation\n");
      return;
   }

   // add code to perform this operation here
   if(doesNameExist(*pHead, name))
   {
      printf("Name already exists in the wait list\n");
      return;
   }
   else
   {
      printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
      addToList(pHead, name, size, called);
   }
}


void doWaiting (groupPointer pHead, int debugMode)
{
   /* get group name from input */
   char *name = getName();
   if (NULL == name)
   {
      printf ("Error: Waiting command requires a name to be given\n");
      printf ("Waiting command is of form: w <name>\n");
      printf ("  where: <name> is the name of the group that is now waiting\n");
      return;
   }

   // add code to perform this operation here
   if(!doesNameExist(pHead, name))
   {
      printf("Name does not exists in the wait list\n");
      return;
   }

   if(updateStatus(pHead, name, debugMode) == FALSE)
   {
      printf("The group are already in the store waiting\n");
      return;
   }
   else
   {
      printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);
      updateStatus(pHead, name, debugMode);
   }
}


void doRetrieve (groupPointer *pHead, int debugMode)
{
   char *theGroup;
   /* get table size from input */
   int size = getPosInt();
   if (size < 1)
   {
      printf ("Error: Retrieve command requires an integer value of at least 1\n");
      printf ("Retrieve command is of form: r <size>\n");
      printf ("  where: <size> is the size of the group making the reservation\n");
      return;
   }
   clearToEoln();
   printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

   // add code to perform this operation here
   theGroup = retrieveAndRemove(pHead, size, debugMode);
}


void doList (groupPointer pHead, int debugMode)
{
   int groupCount;
   /* get group name from input */
   char *name = getName();
   if (NULL == name)
   {
      printf ("Error: List command requires a name to be given\n");
      printf ("List command is of form: l <name>\n");
      printf ("  where: <name> is the name of the group to inquire about\n");
      return;
   }

   // add code to perform this operation here
   if(!doesNameExist(pHead, name))
   {
      printf("Name does not exists in the wait list\n");
      return;
   }
   else
   {
      groupCount = countGroupsAhead(pHead, name, debugMode);

      printf ("Group \"%s\" is behind %d groups\n\n", name, groupCount);

      displayGroupSizeAhead(pHead, name);
   }
}


void doDisplay (groupPointer pHead)
{
   clearToEoln();
   printf ("Display information about all groups\n\n");

   // add code to perform this operation here
   displayListInformation(pHead);
}
