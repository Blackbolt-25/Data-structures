//Using list 
//Using array

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 3

typedef struct node
{
    int data;
    struct node* next;
}NODE;

typedef struct 
{
    int capaciity;
    int n;
    NODE* head;
    NODE* rear;
}CIRCULAR_QUEUE;

int isfull(CIRCULAR_QUEUE* p)
{
    return p->capaciity==p->n;
}

int isempty(CIRCULAR_QUEUE *p)
{
    return p->head==NULL && p->rear==NULL;
}

void initlize(CIRCULAR_QUEUE *p)
{
    p->head=NULL;
    p->rear=NULL;
    p->n=0;
}

void enqueue(CIRCULAR_QUEUE *p,int value)
{
    if(isfull(p))
        printf("The list is full\n");
    else if(isempty(p))
    {
        NODE* newnode=(NODE*)malloc(sizeof(NODE));
        newnode->data=value;
        newnode->next=newnode;
        p->head=newnode;p->rear=newnode;
        p->n++;
    }
    else 
    {
        NODE* newnode=(NODE*)malloc(sizeof(NODE));
        newnode->data=value;
        newnode->next=p->head;
        p->rear->next=newnode;
        p->rear=newnode;
        p->n++;
    }
}
void dequeue(CIRCULAR_QUEUE *p)
{
    if(isempty(p))
        printf("The list is empty\n");
    else if(p->head==p->rear)
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
        p->rear->next=p->head;
        p->n--;
    }
}

void peek(CIRCULAR_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else
        printf("The top element is %d\n",p->head->data);
}

void display(CIRCULAR_QUEUE *p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else
    {
        NODE* temp=p->head;
        do
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
        } while (temp!=p->head);
    }
}

typedef struct node_a
{
    int arr[MAX_SIZE];
    int head;
    int rear;
}CIRCULAR_QUEUE_A;

int isfull_a(CIRCULAR_QUEUE_A *p)
{
    return (p->head==0 && p->rear==MAX_SIZE-1) || p->rear==p->head-1;
}

int isempty_a(CIRCULAR_QUEUE_A *p)
{
    return p->head==-1 && p->rear==-1;
}

void initlize_a(CIRCULAR_QUEUE_A *p)
{
    p->rear=-1;
    p->head=-1;
}

void enqueue_a(CIRCULAR_QUEUE_A *p,int value)
{
    if(isfull_a(p))
        printf("The queue is full\n");
    else if(isempty_a(p))
    {
        p->arr[++p->rear]=value;
        p->head++;
    }
    else
    {
        p->rear++;
        p->rear=p->rear%MAX_SIZE;
        p->arr[p->rear]=value;
    }
}

void dequeue_a(CIRCULAR_QUEUE_A *p)
{
    if(isempty_a(p))
        printf("The queue is empty\n");
    else if(p->head==p->rear)
    {
        printf("The deleted element is %d\n",p->arr[p->head]);
        p->head=-1;
        p->rear=-1;
    }
    else
    {
        printf("The deleted element is %d\n",p->arr[p->head++]);
        p->head=p->head%MAX_SIZE;
    }
}

void peek_a(CIRCULAR_QUEUE_A *p)
{
    if(isempty_a(p))
        printf("The queue is empty\n");
    else
        printf("The top element is %d\n",p->arr[p->head]);
}

void display_a(CIRCULAR_QUEUE_A *p)
{
    if(isempty_a(p))
        printf("The queue is empty\n");
    else
    {
        for(int i=p->head;i<=MAX_SIZE;i++)
        {
            if(i==p->head && i==p->rear)
            {
                printf("%d-->head & rear\n",p->arr[i]);
                break;
            }
            else if(i==MAX_SIZE)
            {
                for(int i=0;i<=p->rear;i++)
                {
                    if(i==p->rear)
                    {
                        printf("%d-->rear\n",p->arr[p->rear]);
                        break;
                    }
                    printf("%d\n",p->arr[i]);
                }
            }
            else 
            {
                if(i==p->head)
                    printf("%d-->head\n",p->arr[i]);    
                else if(i==p->rear)
                {
                    printf("%d-->rear\n",p->arr[p->rear]);
                    return;
                }            
                else
                        printf("%d\n",p->arr[i]);
            }
        }
    }
}


int main()
{
    int choice,temp;
    printf("1.Using Linked list\n2.Using Array\nEnter your choice:-\n");scanf("%d",&choice);
    if(choice==1)
    {
        CIRCULAR_QUEUE p;
        initlize(&p);
        printf("Enter the capacity:-\n");scanf("%d",&p.capaciity);
        while(1)
        {
            printf("1.Insert\n2.Delete\n3.Peek\n4.Display\n5.Exit\nEnter choice:-\n");scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    printf("Enter the element to be inserted:-");
                    scanf("%d",&temp);
                    enqueue(&p,temp);
                    break;
                case 2:
                    dequeue(&p);
                    break;
                case 3:
                    peek(&p);
                    break;
                case 4:
                    display(&p);
                    break;
                case 5:
                    printf("BYE BYE!!!\n");
                    return(0);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }
    }
    else if(choice==2)
    {
        CIRCULAR_QUEUE_A p;
        initlize_a(&p);
        while(1)
        {
            printf("1.Insert\n2.Delete\n3.Peek\n4.Display\n5.Exit\nEnter choice:-\n");scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    printf("Enter the element to be inserted:-");
                    scanf("%d",&temp);
                    enqueue_a(&p,temp);
                    break;
                case 2:
                    dequeue_a(&p);
                    break;
                case 3:
                    peek_a(&p);
                    break;
                case 4:
                    display_a(&p);
                    break;
                case 5:
                    printf("BYE BYE!!!\n");
                    return(0);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }
    }
}
