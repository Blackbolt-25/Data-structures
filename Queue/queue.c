//Types of queues
//i)Simple queue.
//ii)Circular queue
//iii)Double queue
//iv)Priority queue

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct queue
{
    int arr[MAX_SIZE];
    int rear;
    int head;
}QUEUE;

void initlize(QUEUE *p)
{
    p->rear=-1;
    p->head=-1;
}

void enqueue(QUEUE *p,int temp)
{
    if(p->rear+1==MAX_SIZE)
        printf("QUEUE is full\n");
    else
        p->arr[++p->rear]=temp;
}

void dequeue(QUEUE *p)
{
    if(p->rear==p->head) 
        printf("The queue is empty\n");
    else
        printf("The deleted element is %d\n",p->arr[++p->head]);
}

void display(QUEUE *p)
{
    if(p->rear==p->head)
        printf("The queue is empty\n");
    else 
    {
        for(int i=p->rear;i>p->head;i--)
            printf("%d ",p->arr[i]);  
        printf("\n");
    }
}

void peek(QUEUE *p)
{
    if(p->rear==p->head)
        printf("The queue is empty\n");
    else
        printf("The top element is %d\n",p->arr[p->head+1]);
}

typedef struct node
{
    int data;
    struct queue *next;
}NODE;

typedef struct 
{
    NODE * head;
    NODE * rear;
}QUEUE_l;

int isempty(QUEUE_l *p)
{
    return p->rear==NULL && p->head==NULL;
}

void initlize_l(QUEUE_l *p)
{
    p->head=NULL;
    p->rear=NULL;
}

void l_enqueue(QUEUE_l *p, int value)
{
    NODE *newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;
    newnode->next = NULL;
    if (isempty(p))
    {
        initlize_l(p);
        p->head = newnode;
        p->rear = newnode;
    }
    else
    {
        p->rear->next = newnode;
        p->rear = newnode;
    }
}

void l_dequeue(QUEUE_l *p)
{
    if (isempty(p))
        printf("The queue is empty\n");
    else if(p->head==p->rear)
    {
        printf("The deleted element is %d\n", p->head->data);
        free(p->head);
        p->head=NULL;
        p->rear=NULL;
    }
    else
    {
        printf("The deleted element is %d\n", p->head->data);
        NODE* temp = p->head;
        p->head = p->head->next;
        free(temp);
    }
}


void l_peek(QUEUE_l*p)
{
    if(isempty(p))
        printf("The list is empty\n");
    else
        printf("The top element is %d\n",p->head->data);
}

void l_display(QUEUE_l *p)
{
    if(isempty(p))
        printf("The list is empty\n");
    else
    {
        NODE* temp=p->head;
        while (temp!=NULL)
        {
            if(temp==p->head)
                printf("%d-->Head\n",temp->data);
            else if(temp==p->rear)
                printf("%d-->Rear\n",temp->data);
            else
                printf("%d\n",temp->data);
            temp=temp->next;
        }
    }
}

int main()
{
    int choice;
    while(1)
    {
        printf("1.Using Array\n2.Using Linked List\nEnter your choice:-");
        scanf("%d",&choice);
        if(choice==1)
        {
            while(1)
            {
                QUEUE a;
                initlize(&a);
                int temp;
                printf("1.ENQUEUE\n2.DEQUEUE\n3.PEEK\n4.DISPLAY\n5.EXIT\nEnter your choice:-");
                scanf("%d",&choice);
                switch (choice)
                {
                    case 1:
                        printf("Enter the data to be inserted:-\n");
                        scanf("%d",&temp);
                        enqueue(&a,temp);
                        break;
                    case 2:
                        dequeue(&a);
                        break;
                    case 3:
                        peek(&a);
                        break;
                    case 4:
                        display(&a);
                        break;
                    case 5:
                        return(0);
                    default:
                        printf("Wrong choice entered\n");
                        break;
                }
            }
        }
        else if(choice==2)
        {
            while(1)
            {
                QUEUE_l p;
                int temp;
                printf("1.ENQUEUE\n2.DEQUEUE\n3.PEEK\n4.DISPLAY\n5.EXIT\nEnter your choice:-");
                scanf("%d",&choice);
                switch (choice)
                {
                    case 1:
                        printf("Enter the data to be inserted:-\n");
                        scanf("%d",&temp);
                        l_enqueue(&p,temp);
                        break;
                    case 2:
                        l_dequeue(&p);
                        break;
                    case 3:
                        l_peek(&p);
                        break;
                    case 4:
                        l_display(&p);
                        break;
                    case 5:
                        return(0);
                    default:
                        printf("Wrong choice entered\n");
                        break;
                }
            }
        }
    }
}

