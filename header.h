#ifndef HEADER_FILE
#define HEADER_FILE
#include<stdbool.h>

struct Node 
{ 
  char data[30];
  struct Node *next; 
}; 

struct Node* head;
void append(struct Node** head_ref,char new_data[]);
void printList(struct Node *node);
bool isNumber(char *s); 
void verifictaion_function(char *verification);
void analyse();
#endif