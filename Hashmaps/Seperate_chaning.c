#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
  char* key;
  int value;
  struct node *next;
}NODE;

typedef struct hash{
  int capacity;
  NODE* hash_p;
}HASH;

HASH* init(int capacity)
{
  HASH* new=(HASH*)malloc(sizeof(HASH));
  new->capacity=capacity;
  new->hash_p=(NODE*)malloc(sizeof(NODE)*capacity);
  NODE* temp=new->hash_p;
  for(int i=0;i<capacity;i++)
  {
    temp->next=NULL;
    temp++;
  }
  return new;
}


NODE* create_node(char* key,int value)
{
  NODE* newnode=(NODE*)malloc(sizeof(NODE));
  newnode->key=key;
  newnode->value=value;
  newnode->next=NULL;
  return newnode;
}

int hash_function(char* key)
{
  int hash_value=0;
  for(int i=0;i<strlen(key);i++)
  {
    hash_value+=(int)key[i];
    hash_value*=10;
  }
  return hash_value/10;
}

//Insert using separate chaining.
void insert(char* key,int value,HASH* h)
{
  int hash_value=hash_function(key)%h->capacity;
  NODE* temp=h->hash_p;
  if((temp[hash_value]).value && (temp[hash_value]).key!=key)
  {
    temp=temp->next;
    while(temp->next!=NULL && temp->key!=key)
      temp=temp->next;
    if(temp->next==NULL && temp->key!=key)
    {
      NODE* newnode=create_node(key,value);
      temp->next=newnode;
    }
    else
      temp->value=value;
  }
  else
  {
    (temp[hash_value]).key=key;
    (temp[hash_value]).value=value;
  }
}
int retrive(char* key,HASH* h)
{
  int hash_value=hash_function(key) % h->capacity;
  NODE* temp = &(h->hash_p)[hash_value];
  while(temp!=NULL && temp->key!=key)
    temp=temp->next;
  if(temp!=NULL)
    return temp->value;
  return -1;
}

int compare(char *c1,char *c2)
{
  int m= strlen(c1) > strlen(c2) ? strlen(c1) : strlen(c2);
  for(int i=0;i<m;i++)
  {
    if(c1[i]!=c2[i])
      return 0;
  }
  return 1;
}


void delete(char* key,HASH* h)
{
  int hash_value=hash_function(key) % h->capacity;
  NODE* temp = &(h->hash_p)[hash_value];
  NODE* prev=temp;
  while(temp!=NULL && temp->key!=key)
  {
    if(temp==prev)
    {
      temp=temp->next;
      continue;
    }
    temp=temp->next;
    prev=prev->next;
  }
  if(temp==NULL)
    printf("The key %s was not found in the hashmap\n",key);
  else if(temp==prev)
  {
    if(temp->next==NULL)
    {
      printf("Successfully deleted\n");
      temp->key='\0';
      temp->value=0;
      return;
    }
    printf("Successfully deleted\n");
    temp->key=temp->next->key;
    temp->value=temp->next->value;
    NODE* temp2=temp->next;
    temp->next=temp2->next;
    free(temp2);
    return;
  }
  else
  {
    printf("Successfully deleted\n");
    prev->next=temp->next;
    free(temp);
  }
}


int main()
{
  HASH* h; 
  int c;
  printf("Enter the capacity of the hashmap:- ");
  scanf("%d",&c);
  h=init(c);
  int choice;
  char* key;
  int value;
  while(1)   
  {
    printf("1.Insert\n2.Retrive\n3.Delete\n4.Exit\nEnter your choice:-");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:
        printf("Enter the key:-");
        scanf("%s",key);
        printf("Enter the value:-");
        scanf("%d",&value);
        insert(key,value,h);
        break;
      case 2:
        printf("Enter the key-value pair to be retrived:- ");
        scanf("%s",key);
        value=retrive(key,h);
        if(value==-1)
          printf("The key was not found\n");
        else
          printf("The value retrived is:- %d\n",value);
        break;
      case 3:
        printf("Enter the key-value pair to be deleted:- ");
        scanf("%s",key);
        delete(key,h);
        break;
      case 4:
        printf("BYE BYE!!!\n");
        return(0);
      default:
        printf("Invalid choice\n");
        break;
    }
  }
}
