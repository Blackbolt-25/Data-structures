#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_SIZE 100


typedef struct node{
  char data;
  struct node* right;
  struct node* left;
}NODE;

typedef struct stack{
  NODE* stack[MAX_SIZE];
  int top;
}STACK;

NODE* create(char data)
{
  NODE* newnode= (NODE*)malloc(sizeof(NODE));
  newnode->right=NULL;
  newnode->left=NULL;
  newnode->data=data;
  return newnode;
}

void init_s(STACK** s);
void build_postfix_expression(char* str, NODE** head);
void build_prefix_expression(char* str, NODE** head);
int is_operator(char data);
int eval_expression(NODE* head);


int main()
{
  int choice;  
  NODE* head= NULL;
  char str[MAX_SIZE];
  printf("1.Prefix expression\n2.Postfix expression\nEnter your choice:-");
  scanf(" %d",&choice);
  switch(choice)
  {
    case 1:
    {
      printf("Enter your Prefix expression:- ");
      scanf(" %s",str);
      build_prefix_expression(str , &head);
      if(head == NULL)
        printf("The entered expression is not correct.\n Please check again\n");
      else
        printf("The evaluated expression is:- %d",eval_expression(head));
      break;
    }
    case 2:
    {
      printf("Enter your Postfix expression:- ");
      scanf(" %s",str);
      build_postfix_expression(str , &head);
      if(head == NULL)
        printf("The entered expression is not correct.\n Please check again\n");
      else
        printf("The evaluated expression is:- %d",eval_expression(head));
      break;
    }
    default:
      printf("Wrong option pls try again\n");
      break;
  }
}


void init_s(STACK** s)
{
  (*s)->top = -1;
}

int is_operator(char data)
{
  return data == '+' || data == '-' || data == '/' || data =='%' || data == '^' || data == '*';
}

void build_postfix_expression(char* str, NODE** head)
{
  STACK* s;
  init_s(&s);
  for(int i=0;i<strlen(str);i++)
  {
    if(!is_operator(str[i]))
    {
      NODE* newnode = create(str[i]);
      s->stack[++s->top] = newnode;
    }
    else
    {
      NODE* current = create(str[i]);
      NODE* right = s->stack[s->top--];
      NODE* left = s->stack[s->top--];
      current->left=left;
      current->right=right;
      s->stack[++s->top] = current;
    }
  }
  if(s->top == 0)
    *head = s->stack[s->top--];
  else
    *head = NULL;
}

void build_prefix_expression(char* str, NODE** head)
{
  STACK* s;
  init_s(&s);
  for(int i=strlen(str) - 1;i>=0;i--)
  {
    if(!is_operator(str[i]))
    {
      NODE* newnode = create(str[i]);
      s->stack[++s->top] = newnode;
    }
    else
    {
      NODE* current = create(str[i]);
      NODE* left = s->stack[s->top--];
      NODE* right = s->stack[s->top--];
      current->left=left;
      current->right=right;
      s->stack[++s->top] = current;
    }
  }
  if(s->top == 0)
    *head = s->stack[s->top];
  else
    *head = NULL;
}


int eval_expression(NODE* head)
{
  if(head == NULL)
    return 0;
  else if(!is_operator(head->data))
      return head->data - '0';
  char temp = head->data;
  switch(temp)
  {
    case '+':
      return eval_expression(head->left) + eval_expression(head->right);
    case '-':
      return eval_expression(head->left) - eval_expression(head->right);
    case '/':
      return eval_expression(head->left) / eval_expression(head->right);
    case '%':
      return eval_expression(head->left) % eval_expression(head->right);
    case '^':
      return pow(eval_expression(head->left),eval_expression(head->right));
    case '*':
      return eval_expression(head->left) * eval_expression(head->right);
  }
  return 0;
}


