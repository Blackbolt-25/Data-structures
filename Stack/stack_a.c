#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct stack
{
    int stack[MAX_SIZE];
    int top;
}STACK;

void initialize(STACK** stack);

int isempty(STACK** stack);

int isfull(STACK** stack);

void push(STACK** stack,int data);

int pop(STACK** stack);

void peek(STACK** stack);

void display(STACK** stack);

int main()
{
    STACK *p=(STACK*)malloc(sizeof(STACK));
    initialize(&p);
    int choice,data;
    while(1)
    {
        printf("1.Push\n2.Pop\n3.Display\n4.Isempty\n5.Isfull\n6.Peek\n7.Exit\nEnter you choice:-");scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("PUSH\n");
                printf("Enter data:-");scanf("%d",&data);
                push(&p,data);
                break;
            case 2:
                printf("POP\n");
                pop(&p);
                break;
            case 3:
                printf("DISPLAY\n");
                display(&p);
                break;
            case 4:
                printf("ISEMPTY\n");
                if(isempty(&p))
                    printf("The stack is empty\n\n");
                else
                    printf("The stack is not empty\n\n");
                break;
            case 5:
                printf("ISFULL\n");
                if(isfull(&p))
                    printf("The stack is full\n\n");
                else
                    printf("The stack is not full\n\n");
                break;
            case 6:
                printf("PEEK\n");
                peek(&p);
                break;
            case 7:
                printf("BYE BYE!!!\n");
                exit(0);
            default:
                printf("Invalid Choice\n\n");
                break;
        }
    }
}

void initialize(STACK** stack)
{
    (*stack)->top=-1;
}

int isempty(STACK** stack)
{
    return ((*stack)->top==-1);
}

int isfull(STACK** stack)
{
    return ((*stack)->top==MAX_SIZE-1);
}

void push(STACK** stack,int data)
{
    if(isfull(stack))
    {
        printf("Stack Overflow. Cant push an element in a full stack\n\n");
        return;
    }
    (*stack)->stack[++(*stack)->top]=data;
    printf("Data pushed successfully\n\n");
}

int pop(STACK** stack)
{
    if(isempty(stack))
    {
        printf("Stack overflow. Cant pop an empty stack\n\n");
        return -1;
    }
    else
    {
        printf("Data pop-ed successfully\n\n"); 
        return (*stack)->stack[(*stack)->top--];
    }
}

void display(STACK** stack)
{
    if(isempty(stack))
        printf("The stack is empty\n");
    else
    {
        int temp=(*stack)->top;
        for(int i=0;i<temp+1;i++)
            printf("%d\n",(*stack)->stack[i]);
    }
    printf("\n");
}

void peek(STACK** stack)
{
    if((*stack)->top==-1)
        printf("The stack is empty\n\n");
    else
        printf("The top element is:- %d\n\n",((*stack)->stack[(*stack)->top]));
}



