//  Abstract Data Type (ADT):- Set of operations to be performed on user defined data types without implementation details.
// Implementation of List using array.

//Write a c program to implement a list using array and perform the following operation.
// i)insert head.
// ii)insert tail.
// iii)delete at index.
// iv)Display.

//Imp q.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100

struct list
{
    int arr[MAX_SIZE];
    int size;
};

void init(struct list*lst)
{
    lst->size=0;
}

int isFull(struct list *lst)
{
    return lst->size==MAX_SIZE;
}

int isempty(struct list *lst)
{
    return lst->size==0;
}

void insertTail(struct list *lst, int value)
{
    if(isempty(lst))
    {
        lst->arr[0]=value;
        lst->size++;
        printf("Data added at 0th successfully.\n\n");
        return;
    }
    else if(isFull(lst))
    {
        printf("The list is full.\n\n");
        return;
    }
    lst->arr[lst->size]=value;
    lst->size++;
    printf("Data added at tail successfully.\n\n");
}

void insertHead(struct list *lst, int value)
{
    if(isempty(lst))
    {
        lst->arr[0]=value;
        lst->size++;
        printf("Data added at 0th successfully.\n\n");
        return;
    }
    else if(isFull(lst))
    {
        printf("The list is full.\n\n");
        return;
    }
    int size=lst->size;
    for(int i=size;i>0;i--)
    {
        lst->arr[i]=lst->arr[i-1];
    }
    lst->arr[0]=value;
    lst->size++;
    printf("Data added at head successfully.\n\n");
}

void delete(struct list *lst ,int value)
{
    if(isempty(lst))
    {
        printf("The list is empty.\n\n");
        return;
    }
    for(int i=0;i<lst->size;i++)
    {
        if(lst->arr[i]==value)
        {
            for(int j=i;j<lst->size;j++)
            {
                lst->arr[j]=lst->arr[j+1];
            }
            lst->arr[lst->size-1]=0;
            lst->size--;
            printf("Data of value %d deleted successfully.\n\n",value);
            return;
        }
    }
    printf("Value not found in the list.\n\n");
}

void display(struct list *lst)
{
    printf("The List is:-\n");
    if(isempty(lst))
    {
        printf("Empty\n\n");
        return;
    }
    for(int i=0;i<lst->size;i++)
    {
        printf("%d ",lst->arr[i]);
    }   
    printf("\n\n");
}


typedef struct node
{
    int data;
    struct node *link;
}NODE;


NODE* create_node(int data)
{
    NODE* temp=(NODE*)malloc(sizeof(NODE));
    temp->data=data;
    temp->link=NULL;
    return temp;
}

void insert_back(NODE **start,int value)
{
    if(*start==NULL)
    {
        NODE* newnode=create_node(value);
        *start=newnode;
        return;
    }
    NODE* temp=*start;
    while(temp->link!=NULL)
        temp=temp->link;
    NODE* newnode=create_node(value);
    temp->link=newnode;
}

void l_l(struct list *l1)
{
    NODE* head=NULL;
    for(int i=0;i<l1->size;i++)
    {
        insert_back(&head,l1->arr[i]);
    }
    printf("Display of the lined list\n");
}

int main()
{
    struct list lst;
    init(&lst);
    int choice,value;
    while(1)
    {
        printf("1: Insert Tail\n");
        printf("2: Insert head\n");
        printf("3: Delete value\n");
        printf("4: Covert to linked list\n");
        printf("5: Display\n");
        printf("6: Exit\n");
        printf("Enter choice:-\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 :printf("Enter the value\n");
                    scanf("%d",&value);
                    insertTail(&lst,value);
                    break;
            case 2 :printf("Enter the value\n");
                    scanf("%d",&value);
                    insertHead(&lst,value);
                    break;
            case 3 :printf("Enter the value\n");
                    scanf("%d",&value);
                    delete(&lst,value);
                    break;
            case 4:l_l(&lst);
            case 5: display(&lst);
                    break;
            case 6:
                    exit(0);
            default : printf("Invalid choice.\n");

        }
    }
}
