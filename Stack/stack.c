//Application of stack:-
//Infix -> Postfix , Prefix
//Paranthesis Eval
//Postfix Eval
//If we enconter operands append it to the postfix expression.
//However if we get an operator we append it to the stack.
//Associativity and Precedence :-
//Associativity- Whether the expression should be evaluated from left to right or vice-versa.
//Precedence- Operator precedence: Rules:- 1.)() (Brackets)--0
                                    //     2.)+ - --1
                                    //     3.) * / -- 2
                                    //     4.) ^ -- 3
//Higher priority operator can be stored above the lower priority operator but not vice-versa.
//Whenever operator is having equal or less priority that operator has to be poped then pushed to the postfix expression.


#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int data;
    struct stack *next;
}STACK;

STACK *create(int value)
{
    STACK *temp=(STACK*)malloc(sizeof(STACK));
    temp->data=value;
    temp->next=NULL;
    return temp;
}

void push(STACK **top)
{
    int value;
    printf("Enter value to enter:-");scanf("%d",&value);
    STACK *temp=create(value);
    if(*top==NULL)
    {
        *top=temp;
        printf("Data added successfully\n\n");
        return;
    }
    temp->next=*top;
    *top=temp;
    printf("Data added successfully\n\n");
}

int pop(STACK **top)
{
    if(*top==NULL)
    {
        return -1;
    }
    else
    {
        STACK *temp=*top;
        *top=temp->next;
        int var=temp->data;
        free(temp);
        return var;
    }  
}

void display(STACK **top)
{
    if(*top==NULL)
    {
        printf("The stack is empty and the size is %d.\n\n",0);
        return;
    }
    int count=0;
    STACK *temp=*top;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
        count++;
    }
    printf("The size of the stack is %d\n\n",count);
}

void first(STACK **top)
{
    if(*top==NULL)
        printf("The stack is empty.\n\n");
    else
        printf("The top element is %d.\n\n",(*top)->data);
}

int isempty(STACK** top)
{
    if(*top==NULL)
        return 1;
    else
        return 0;
}

int main()
{
    STACK *top=NULL;
    int choice;
    printf("STACK\n");
    while(1)
    {
        printf("1.To push a element\n2.To pop an element\n3.To dispaly and see the size of stack \n4.To see top element of stack\n5.To check if the stack is empty\n6.To exit\n");
        printf("Enter choice:-");scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("\nPUSH\n");
                push(&top);
                break;
            case 2:
                printf("\nPOP\n");
                int temp=pop(&top);
                if(temp==-1)
                    printf("%d\n\n",-1);
                else
                    printf("The poop-ed element is:- %d\n\n",temp);
                break;
            case 3:
                printf("\nDISPLAY\n");
                display(&top);
                break;
            case 4:
                printf("\nTOP\n");
                first(&top);
                break;
            case 5:
                printf("\nISEMPTY\n");
                temp=isempty(&top);
                if(temp==1)
                    printf("The stack is empty\n\n");
                else
                    printf("The stack is not empty\n\n");
                break;
            case 6:
                printf("BYE BYE!!!\n");
                exit(0);
        }
    }
}