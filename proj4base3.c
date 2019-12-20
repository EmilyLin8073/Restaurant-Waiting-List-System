#include "proj4base.h"


//In this function, we are going to add node to the list
void addToList(groupPointer *pHead, char *name, int size, STATUS status)
{
   //Create a new node
   groupPointer pTemp = (groupPointer)malloc(sizeof(Node));
   pTemp->g1.name = (char*)malloc(sizeof(char)*(30));

   //Copy the name of the group
   strcpy(pTemp->g1.name, name);

   //Assign the size to the node
   pTemp->g1.size = size;

   //Checking the status and assign it to the node
   if(status == waiting)
      pTemp->g1.status = waiting;
   else
      pTemp->g1.status = called;

   //First, assign pNext equal to NULL
   pTemp->pNext = NULL;

   //We add the node at the end of the list(FIFO)
   if((*pHead) == NULL)
   {
      (*pHead) = pTemp;
      return;
   }
   else
   {
      groupPointer pTemp2 = *pHead;

      while(pTemp2->pNext != NULL)
      {
         pTemp2 = pTemp2->pNext;
      }

      pTemp2->pNext = pTemp;
   }
}


//In this function, we are going to check whether the name is already on the list or not
int doesNameExist(groupPointer pHead, char *name)
{
   //A loop traverse the whole list, if the name is not on the list
   while(pHead != NULL)
   {
      if (!strcmp(name, pHead->g1.name))
         return TRUE;

      pHead = pHead->pNext;
   }
   return FALSE;
}


//In ths function, we are going the update the status for the group
int updateStatus(groupPointer pHead, char *name, int debugMode)
{
   int i = 1;

   groupPointer temp = pHead;

   //If the list is empty, we print out the statement
   if(pHead == NULL)
   {
      printf("List is empty: Can't Update\n");
      return FALSE;
   }

   if(debugMode == TRUE)
      printf("DEBUG MODE\n#\tName\tSize\tStatus\n");

   //A loop traverse the list to print the group info when the debug mode is on
   while (strcmp(name, pHead->g1.name) && pHead->pNext != NULL)
   {
      if(debugMode == TRUE)
      {
         char *stat;
         if(temp->g1.status == waiting)
            stat = "Present";
         else
            stat = "Not Present";

         printf("%d\t%s\t%d\t%s\n", i, temp->g1.name, temp->g1.size, stat);
         i++;
      }

      pHead = pHead->pNext;
   }

   //A if statement to change the group status when the name is given
   if (!strcmp(pHead->g1.name, name) && pHead->g1.status != waiting)
   {
      pHead->g1.status = waiting;
      return true;
   }

   return FALSE;
}


//In this function, we are going to delete specific node on the list
char *retrieveAndRemove(groupPointer *pHead, int size, int debugMode)
{
   int count = 1;

   groupPointer pTemp = *pHead;
   groupPointer pTemp2;

   //If the list is empty, we print out the statement
   if(pTemp == NULL)
   {
      printf("List empty\n");
      return NULL;
   }

   //Check the first node on the list
   if(pTemp->g1.size <= size && pTemp->g1.status == called)
   {
      *pHead = (*pHead)->pNext;

      free(pTemp);

      //If the debug mode is on, we print out the group info
      if(debugMode == TRUE)
      {
         displayListInformation(*pHead);
      }
      return NULL;
   }

   if(debugMode == TRUE)
      printf("DEBUG MODE\n#\tName\tSize\tStatus\n");

   //A loop traverse the list
   while(pTemp->pNext!= NULL)
   {
      //If the debug mode is on, we print out the group info
      if(debugMode == TRUE)
      {
         char *stat;
         if(pTemp->g1.status == waiting)
            stat = "Present";
         else
            stat = "Not Present";
         printf("%d\t%s\t%d\t%s\n", count, pTemp->g1.name, pTemp->g1.size, stat);
         count++;
      }

      //Check if the gorup size is equal to or less than the table size
      if(pTemp->pNext->g1.size <= size)
      {
         //Check if the group is in store waiting or not
         if(pTemp->pNext->g1.status == waiting)
         {
            pTemp2 = pTemp->pNext;
            pTemp->pNext = pTemp2->pNext;

            free(pTemp2);
            return NULL;
         }
      }
      pTemp = pTemp->pNext;
   }

   //Check the only node on the list
   if(pTemp->pNext == NULL && pTemp->g1.size <= size)
   {
      if(pTemp->g1.status == waiting)
         free(pTemp);

      //If we delete the only node on the list, set head equal to null
      (*pHead) = NULL;

         printf("Now the list is empty\n\n");
      return NULL;
   }
   else
      printf("No valid group size for the table\n"); //If there's no size can fit into the
                                                     //table size, print out the statement

   return NULL;
}


//In this function, we are going to how many size are ahead the group that the name are given
int countGroupsAhead(groupPointer pHead, char *name, int debugMode)
{
   int groupCount = 0;
   int i = 1;

   groupPointer temp = pHead;

   if(debugMode == TRUE)
      printf("DEBUG MODE\n#\tName\tSize\tStatus\n");

   //A loop traverse the list to find the given name
   while(strcmp(name, pHead->g1.name))
   {
      //If the debug mode is on, we print out the group info
      if(debugMode == TRUE)
      {
         char *stat;
         if(temp->g1.status == waiting)
            stat = "Present";
         else
            stat = "Not Present";

         printf("%d\t%s\t%d\t%s\n", i, temp->g1.name, temp->g1.size, stat);
         i++;
      }

      groupCount++;  //A counter to count how many group are ahead the group that are given
      pHead = pHead->pNext;
   }
   return groupCount;
}


//In this function, we are going to display the group info before the group that are given
void displayGroupSizeAhead(groupPointer pHead, char *name)
{
   //If the list is empty, we print out the statement
   if(pHead == NULL)
   {
      printf("List is empty\n");
      return;
   }

   //A loop traverse the list to find the specific name that are given
   while(strcmp(name, pHead->g1.name))
   {
      printf("The group %s of size %d is ahead of %s \n", pHead->g1.name, pHead->g1.size, name);
      pHead = pHead->pNext;
   }
}


//In this function, we are going to print out the group info list
void displayListInformation(groupPointer pHead)
{
   int groupCount = 0;

   //If the list is empty, we print out the statement
   if(pHead == NULL)
   {
      printf("List is empty\n");
      return;
   }

   //A loop traverse the whole list
   while(pHead != NULL)
   {
      //Print out the group info
      printf("The name of the group: %s\n", pHead->g1.name);
      printf("The size of this group: %d\n", pHead->g1.size);

      //Check the status and print out the group status
      switch (pHead->g1.status)
      {
         case waiting:
            printf("Waiting in store\n\n");
            break;
            
         case called:
            printf("Called ahead\n\n");
            break;
      }
      
      pHead = pHead->pNext;
      
      groupCount++;
   }

   //Print out how many groups are waiting
   printf("Total number of waiting groups: %d\n", groupCount);
}





