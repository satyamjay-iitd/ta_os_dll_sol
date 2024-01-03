#include <string.h>

#include "dll.h"


void clear(struct Node **head){
  while(deleteAt(head, 0) == 0);
}

// Compares dll to an array.
// Assuming every element in the list is an int
int isEqualTo(struct Node *head, int* arr, int len){
  struct Node* tail = head;
 
  for(int i=0; i<len; i++){
    if(head == NULL)
      return 0;

    if(arr[i] != head->data)
      return 0;
  
    tail = head->prev;
    head = head -> next;
  }

  if(head != NULL)
    return 0;

  // for(int i=len-1; i>=0; i--){
  //   if(tail == NULL)
  //     return 0;
  //
  //   if(arr[i] != tail->data)
  //     return 0;
  //
  //   tail = tail -> prev;
  // }
  //
  // return tail == NULL;
}


void testInsertAt(){
  printf("\n****************** TESTING INSERT ***************************\n");
  struct Node* head = NULL;

  int arr[] = {100};

  if(insertAt(&head, 0, 100) == 0 && isEqualTo(head, arr, 1))
    printf("Test - 1. Insert at index = 0. Passed\n");
  else
    printf("Test - 1. Insert at index = 0. Failed\n");

  if(insertAt(&head, 1000, 100) == -1 && isEqualTo(head, arr, 1))
    printf("Test - 2. Insert at index > len. Passed\n");
  else
    printf("Test - 2. Insert at index > len. Failed\n");

  int arr2[] = {100, 200};
  if(insertAt(&head, 1, 200) == 0 && isEqualTo(head, arr2, 2))
    printf("Test - 3. Insert at index = len. Passed\n");
  else
    printf("Test - 3. Insert at index = len. Failed\n");

  int arr3[] = {100, 150, 200};
  if(insertAt(&head, 1, 150) == 0 && isEqualTo(head, arr3, 3))
    printf("Test - 4. Insert at 0<index<len. Passed\n");
  else
    printf("Test - 4. Insert at 0<index<len. Failed\n");
 
  clear(&head);

}

void testDeleteAt(){
  printf("\n****************** TESTING DELETE ***************************\n");

  struct Node* head = NULL;

  if(deleteAt(&head, 0) == -1)
    printf("Test - 1.0. Delete from Empty - 1. Passed\n");
  else
    printf("Test - 1.0. Delete from Empty - 1. Failed\n");

  if(deleteAt(&head, 1) == -1)
    printf("Test - 1.1. Delete from Empty - 2. Passed\n");
  else
    printf("Test - 1.1. Delete from Empty - 2. Failed\n");

  insertAt(&head, 0, 400);
  insertAt(&head, 0, 300);
  insertAt(&head, 0, 200);
  insertAt(&head, 0, 100);

  int arr[] = {200, 300, 400};
  if(deleteAt(&head, 0) == 0 && isEqualTo(head, arr, 3))
    printf("Test - 2. Delete at index = 0. Passed\n");
  else
    printf("Test - 2. Delete at index = 0. Failed\n");

  int arr2[] = {200, 400};
  if(deleteAt(&head, 1) == 0 && isEqualTo(head, arr2, 2))
    printf("Test - 3. Delete at 0<index<len. Passed\n");
  else
    printf("Test - 3. Delete at 0<index<len. Failed\n");


  int arr3[] = {200};
  if(deleteAt(&head, 1) == 0 && isEqualTo(head, arr3, 1))
    printf("Test - 4. Insert at index=len-1. Passed\n");
  else
    printf("Test - 4. Insert at index=len-1. Failed\n");

  if(deleteAt(&head, 1) == -1 && isEqualTo(head, arr3, 1))
    printf("Test - 5.1. Insert at len-1<index. Passed\n");
  else
    printf("Test - 5.1. Insert at len-1<index. Failed\n");
 
  if(deleteAt(&head, 2) == -1 && isEqualTo(head, arr3, 1))
    printf("Test - 5.2. Insert at len-1<index. Passed\n");
  else
    printf("Test - 5.2. Insert at len-1<index. Failed\n");

  clear(&head);
}

int _testAt(struct Node* head, int* arr, int len){
  if(at(head, -1) != NULL)
    return 0;

  for(int i=0; i<len; i++){
    if(at(head, i)->data != arr[i])
      return 0;
  }

  if(at(head, len) != NULL)
    return 0;
  
  return 1;
}

void testAt(){
  printf("\n****************** TESTING INDEXING ***************************\n");

  struct Node* head = NULL;

  if(at(head, 0) == NULL)
    printf("Test - 1. Access empty list. Passed\n");
  else
    printf("Test - 1. Access empty list. Failed\n");

  int arr[] = {100, 200, 300, 400};
  int failed = 0;
  for(int i=0; i<4; i++){
    insertAt(&head, i, (i+1)*100);
    if(_testAt(head, arr, i+1) != 1){
      failed = 1; 
      break;
    }
  }
  if(!failed)
    printf("Test - 2. Index after Insert. Passed\n");
  else
    printf("Test - 2. Index after Insert. Failed\n");

  failed = 0;
  for(int i=3; i>=0; i--){
    deleteAt(&head, i);
    if(_testAt(head, arr, i) != 1){
      failed = 1; 
      break;
    }
  }
 if(!failed)
    printf("Test - 3. Index after Delete. Passed\n");
  else
    printf("Test - 3. Index after Delete. Failed\n");

  clear(&head);
}

void testArbitraryDataType(){
  printf("\n****************** TESTING ARBITRARY DATATYPE ***************************\n");

  struct Node* head = NULL;

  int* I = (int*)malloc(sizeof(int));
  *I = 100;
  double* D = (double*)malloc(sizeof(double));
  *D = 100;
  char* S = strdup("300");
  
  insertAt(&head, 0, I);
  insertAt(&head, 1, D);
  insertAt(&head, 2, S);

  int testFail = 0;
  if(*(int*)(at(head, 0)->data) != *I)
    testFail = 1;
  if(*(double*)(at(head, 1)->data) != *D)
    testFail = 1;
  if((char*)(at(head, 2)->data) != S)
    testFail = 1;

  if(testFail)
    printf("Test - 1. Failed\n");
  else
    printf("Test - 1. Passed\n");

  free(I);
  free(D);
  free(S);
  clear(&head);
}

void runTestCases(){
  testInsertAt();
  testDeleteAt();
  testAt();
  testArbitraryDataType();
}


int main(){
  runTestCases();
}
