#include<stdio.h>
#include<stdlib.h>

struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
};

// 0 based index. at(, 0) should give head. at(, size-1) should give tail.
// return NULL if idx is not valid.
struct Node* at(struct Node *head, int idx){
  if(idx < 0)
    return NULL;
 
  for(int i=0; i<idx; i++){
    if(head == NULL)
      return NULL;
    head = head->next;
  }
  return head;
}


// Return 0 if succesful, else -1. (Why will it fail?)
// Semantics of insertAt:-
//  100 -> 200
//      insertAt(0, 99)
//  99 -> 100 -> 200
//      insertAt(3, 201)
//  99 -> 100 -> 200 -> 201
//      insertAt(2, 150)
//  99 -> 100 -> 150 -> 200 -> 201
//      insertAt(999, _)
//  99 -> 100 -> 150 -> 200 -> 201
//      insertAt(-1, _)
//  99 -> 100 -> 150 -> 200 -> 201
int insertAt(struct Node **head, int idx, int data){
  if(idx == -1)
    return -1;

  if(idx == 0){
    struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));

    // Populate newNode;
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;

    // Modify head;
    if(*head != NULL)
      (*head)->prev = newNode;

    *head = newNode;

    return 0;
  }

  struct Node* parent =  at(*head, idx - 1);
  if(parent == NULL)
    return -1;

  struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
  
  // Populate newNode
  newNode->data = data;
  newNode->next = parent -> next;
  newNode->prev = parent;

  // Modify parent
  parent->next = newNode;

  // Modify child
  if(newNode->next != NULL)
    newNode->next->prev = newNode;

  return 0;
}


int deleteAt(struct Node **head, int idx){
  if(idx == -1 || (*head == NULL))
    return -1;


  if(idx == 0){

    struct Node* old_head = *head;

    *head = old_head->next;
    if((*head) != NULL)
      (*head)->prev = NULL;

    free(old_head);

    return 0;
  }

  struct Node* self =  at(*head, idx);
  if(self == NULL)
    return -1;

  // Modify Parent
  self->prev->next = self->next;

  // Modify Child
  if(self->next != NULL)
    self->next->prev = self->prev;

  free(self);

  return 0;
}

void clear(struct Node **head){
  while(deleteAt(head, 0) == 0);
}


void display (struct Node *node)
{
  struct Node *end;
  printf ("\nIn Forward Direction\n");
  while (node != NULL)
    {
      printf (" %d ", node->data);
      end = node;
      node = node->next;
    }

  printf ("\nIn Backward direction \n");
  while (end != NULL)
    {
      printf (" %d ", end->data);
      end = end->prev;
    }
}

void displayAt(struct Node* head, int idx){
  struct Node* n = at(head, idx);
  if(n == NULL)
    printf("NULL\n");
  else
    printf("%d\n", at(head, idx)->data);
}

// Compares dll to an array.
int isEqualTo(struct Node *head, int* arr, int len){
  for(int i=0; i<len; i++){
    if(head == NULL)
      return 0;

    if(arr[i] != head->data)
      return 0;

    head = head -> next;
  }

  return head == NULL;
}
