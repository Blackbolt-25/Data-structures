#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
  char* key;
  int value;
}NODE;

typedef struct hash{
  int capacity;
  NODE* hash_p;
}HASH;

HASH* init(int c)
{
  HASH* h=(HASH*)malloc(sizeof(HASH));
  if(c==0)
  {
    h->hash_p=NULL;
    for(int i=0;i<c;i++)
      ((h->hash_p)[i])->value=0;
  }
  else
    h->hash_p=(NODE*)malloc(sizeof(NODE)*c);
  return h;
}


int hash_function(char* key)
{
 int sum=0;
  for(int i=0;i<strlen(key);i++)
    sum+=(int)key[i];
  return sum;
}

void insert_1(HASH* h,char* key ,int value)     //Linear probing/
{
  if(h->hash_p==NULL)
  {
    printf("The hashmap is empty\n");
    return;
  }
  int hash_value = hash_function(key)%h->capacity;
  NODE* temp=(h->hash_p)[hash_value];
  if(((h->hash_p)[hash_value])->value)
  {
    int var=hash_value;
    while(((h->hash_p)[hash_value])->value)
    {
      hash_value= (hash_value) % h->capacity;
      if(hash_value==var)
        break;
    }
    if(hash_value == var)
    {
      printf("There is no more free space in the hash map\n");
      return;
    }
    ((h->hash_p)[hash_value])->key=key;
    ((h->hash_p)[hash_value])->value=value;
  }
  else
  {
    int hash_value = hash_function(key)%h->capacity;
    ((h->hash_p)[hash_value])->key=key;
    ((h->hash_p)[hash_value])->value=value;
  }
}




int main()
{

}
