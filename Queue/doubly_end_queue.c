#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node * next;
}NODE;

typedef struct queue
{
    NODE* head;
    NODE* rear;
    int n;
    int c;
}DOUBLY_ENDED_QUEUE;

int isfull(DOUBLY_ENDED_QUEUE *p)
{
    return p->c==p->n;
}

int isempty(DOUBLY_ENDED_QUEUE *p)
{
    return p->n==0;
}

void initlize(DOUBLY_ENDED_QUEUE *p)
{
    p->n=0;
    p->head=NULL;
    p->rear=NULL;
}

NODE* create(int value)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=value;
    newnode->next=NULL;
    return newnode;
}

void insert_at_back(DOUBLY_ENDED_QUEUE *p,int value)
{
    if(isfull(p))
        printf("The queue is full\n");
    else if(isempty(p))
    {
        NODE* newnode=create(value);
        p->head=newnode;
        p->rear=newnode;
        p->n++;
    }
    else
    {
        NODE* newnode=create(value);
        p->rear->next=newnode;
        p->rear=newnode;
        p->n++; 
    }   
}

void insert_at_front(DOUBLY_ENDED_QUEUE *p,int value)
{
    if(isfull(p))
        printf("The queue is full\n");
    else if(isempty(p))
    {
        NODE* newnode=create(value);
        p->head=newnode;
        p->rear=newnode;
        p->n++;
    }
    else 
    {
        NODE* newnode=create(value);    
        newnode->next=p->head;
        p->head=newnode;
        p->n++;
    }
}

void delete_at_front(DOUBLY_ENDED_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else if(p->rear==p->head)
    {
        printf("The deleted element is %d\n",p->head->data);
        free(p->head);
        p->head=NULL;
        p->rear=NULL;
        p->n--;
    }
    else
    {
        printf("The deleted element is %d\n",p->head->data);
        NODE* temp=p->head;
        p->head=p->head->next;
        free(temp);
        p->n--;
    }
}

void delete_at_back(DOUBLY_ENDED_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else if(p->head==p->rear)
    {
        printf("The deleted element is %d\n",p->rear->data);
        free(p->rear);
        p->rear=NULL;
        p->head=NULL;
        p->n--;
    }
    else
    {
        printf("The deleted element is %d\n",p->rear->data);    
        NODE* temp=p->head;
        while(temp->next!=p->rear)
            temp=temp->next;
        free(p->rear);
        p->rear=temp;
        p->rear->next=NULL;
        p->n--;
    }
}

void peek(DOUBLY_ENDED_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else    
        printf("The top element is %d\n",p->head->data);
}

void display(DOUBLY_ENDED_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else 
    {
        NODE* temp=p->head;
        while(temp!=NULL)
        {
            if(temp==p->head && temp==p->rear)
                printf("%d-->head & rear\n",temp->data);
            else if(temp==p->head)
                printf("%d-->head\n",temp->data);
            else if(temp==p->rear)
                printf("%d-->rear\n",temp->data);
            else 
                printf("%d\n",temp->data);
            temp=temp->next;
        }
    }
}

int main()
{
    DOUBLY_ENDED_QUEUE p;
    initlize(&p);
    printf("Enter the capacity:-");scanf("%d",&p.c);
    int choice,temp;
    while(1)
        {
            printf("1.Insert at front\n2.Insert at back\n3.Delete at front\n4.Delete at back\n5.Peek\n6.Display\n7.Exit\nEnter your choice:-");scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    printf("Enter the element to be inserted:-");
                    scanf("%d",&temp);
                    insert_at_front(&p,temp);
                    break;
                case 2:
                    printf("Enter the element to be inserted:-");
                    scanf("%d",&temp);
                    insert_at_back(&p,temp);
                    break;
                case 3:
                    delete_at_front(&p);
                    break;
                case 4:
                    delete_at_back(&p);
                    break;
                case 5:
                    peek(&p);
                    break;
                case 6:
                    display(&p);
                    break;
                case 7:
                    printf("BYE BYE!!!\n");
                    return(0);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }
}
