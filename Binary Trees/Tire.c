// Each node can have max 26 children. Insert, delete and search operations to be performed on Trie tree.
// Trie tree applications:-
//   i)Browser history
//   ii)Data compression
//   iii)prefix evaluation and prefix matching in routing algorithum.
//   iv)auto complete and pattern matching
//   Advantages:-
//   i)It would take o(1) time complexity for insert, search and delete operations (best case scenario). Lenth of the string is given as 'n' then TC would be o(*n).
//   Pros:- 
//   i)Easy to implement
//   Cons:-
//   i)Consumes more memory as and when #of strings increases.
   
#include<stdio.h>
#include<stdlib.h>
$include<string.h>
#define alphabet_size 26

typedef struct node{
  char data;
  struct node* next;
}NODE;

typedef struct tree{
  NODE* root[alphabet_size];
  int eod;
}TREE;

TREE* createTree()
{
  TREE* newtree= (TREE*) malloc(sizeof(TREE));
  for(int i=0;i<26;i++)
    newtree->root[i]=NULL;
  newtree->eod = 0;
  return newtree;
}

NODE* createnode(char data)
{
  NODE* newnode= (NODE*)malloc(sizeof(NODE));
  newnode->data=data;
  newnode->next=NULL;
  return newnode;
}

void insert(const char* word,TREE* head)
{
  NODE* current =head;
  for(int i=0;i<strlen(word);i++)
  {
    int index = word[i] - 'a';
    if(!current->root[index])
    {
      NODE* newnode= createnode(word[i]);
      current->root[index] = newnode;
      (current->root[index])->next = createTree();
    }
    current = (current->root[index])->next;
    if(strlen(word) - 1 == i)
      current->eod = 1;
    else
      current->eod = 0;
  }
}

void printword(const char * word,TREE * head)
{
  TREE* current = head;
  char* str = word;
  char* ans = "";
  while(*str)
  {
    int index = *str - 'a';
    if(!current -> root[index])
      break;
    current = (current->root[index])->next;
    strcat(ans,*str);
    if(strlen(word) - 1 == i && current->eod)
    {
      printf("The word searched is %s\n",str);
      return; 
    }
  }
  printf("The word that was given was not in the Trie tree\n");
}


int main()
{
  TREE*  
}


