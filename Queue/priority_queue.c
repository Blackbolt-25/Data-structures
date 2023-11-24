// By creating a different data struct itself.

#include<stdio.h>
#include<stdlib.h>

struct structure
{
    int data;
    int weightage;
    struct structure* next;
};

typedef struct node
{   
    struct structure* head;
    struct structure* rear;
    int capacity;
    int size;
}NODE;

int isfull(NODE* p)
{
    return p->capacity==p->size;
}

int isempty(NODE* p)
{
    return p->head==NULL && p->rear==NULL;
}

void init(NODE* p,int c)
{
    p->capacity=c;
    p->size=0;
    p->head=p->rear=NULL;
}

struct structure* create(int value,int weight)
{
    struct structure *a=(struct structure*)malloc(sizeof(struct structure));
    a->data=value;
    a->weightage=weight;
    a->next=NULL;
    return a;
}

void enqueue(NODE* p,int value,int weight)
{
    if(isfull(p))
        printf("The queue is full\n");
    else if(isempty(p))
    {
        struct structure* newnode=create(value,weight);
        p->head=newnode;
        p->rear=newnode;
        p->size++;
    }
    else
    {
        struct structure* newnode=create(value,weight);
        struct structure* temp=p->head;
        if(p->head==p->rear || p->head->weightage<=newnode->weightage)
        {
            if((((p->head->weightage==newnode->weightage && p->head->data>newnode->data) || p->head->weightage>newnode->weightage)) && p->head==p->rear)
            {
                newnode->next=p->head->next;
                p->head->next=newnode;
                p->rear=newnode;
                p->size++;
                printf("Data inserted\n");
                return;
            }
            else if((p->head->weightage==newnode->weightage && p->head->data<newnode->data) || p->head->weightage<newnode->weightage)
            {
                newnode->next=p->head;
                p->head=newnode;
                p->size++;
                printf("Data inserted\n");
                return;
            }
        }
        while(temp->next!=NULL)
        {
            if(temp->next->weightage<=newnode->weightage)
            {
                if((temp->next->weightage==newnode->weightage && newnode->data>temp->next->data) || temp->next->data<newnode->weightage)
                {
                    newnode->next=temp->next;
                    temp->next=newnode;
                    p->size++;
                    printf("Data inserted\n");
                    return;
                }
            }
            temp=temp->next;
        }
        temp->next=newnode;
        p->rear=newnode;
        p->size++;
        printf("Data inserted\n");
    }
}


int dequeue(NODE* p)
{
    if(isempty(p))
    {
        printf("The queue is empt\n");
        return -1;
    }
    else if(p->head==p->rear)
    {
        int value=p->head->data;
        free(p->head);
        p->head=p->rear=NULL;
        return value;
    }
    else
    {
        int value=p->head->data;
        struct structure* temp=p->head;
        p->head=p->head->next;
        free(temp);
        return value;
    }
}

void peek(NODE* p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else    
        printf("The top element is:- %d\n",p->head->data);
}

void display(NODE* p)
{
    if(isempty(p))
        printf("The queue is empty\n");
    else
    {
        struct structure* temp=p->head;
        while(temp!=NULL)
        {
            if(temp==p->head && temp==p->rear)
                printf("%d --> head & rear\n",temp->data);
            else if(temp==p->head)
                printf("%d --> head\n",temp->data);
            else if(temp==p->rear)
                printf("%d --> rear\n",temp->data);
            else
                printf("%d\n",temp->data);
            temp=temp->next;
        }
    }
}

int main()
{
    int choice,capacity,value,weight;
    NODE ans;
    printf("Enter the capacity:- ");
    scanf("%d",&capacity);
    init(&ans,capacity);
    while(1)
    {
        printf("1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Exit\nEnter your choice:-");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("Enter the value:- ");scanf("%d",&value);
                printf("Enter the weight:- ");scanf("%d",&weight);
                enqueue(&ans,value,weight);
                break;
            case 2:
                value=dequeue(&ans);
                if(value!=-1)
                    printf("The popped element is:- %d\n",value);
                break;
            case 3:
                peek(&ans);
                break;
            case 4:
                display(&ans);
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

//Using Arrays:- (More easier)

// #include<stdio.h>
// #include<stdlib.h>
// #define MAX_SIZE 5

// typedef struct node
// {
//     int data[MAX_SIZE];
//     int weight[MAX_SIZE];
//     int head;
//     int rear;
// }NODE;

// void init(NODE* p)
// {
//     p->head=-1;
//     p->rear=-1;
// }   

// int isfull(NODE* p)
// {
//     return p->rear+1==MAX_SIZE;
// }

// int isempty(NODE *p)
// {
//     return p->rear==-1 && p->head==-1;
// }

// void enqueue(NODE* p,int data,int weight)
// {       
//     if(isfull(p))
//         printf("The queue is full\n");
//     else if(isempty(p))
//     {
//         p->data[++p->rear]=data;
//         p->weight[++p->head]=weight;
//         printf("Data inserted\n");
//     }
//     else
//     {
//         int index=p->rear+1;
//         for(int i=p->head;i<p->rear+1;i++)
//         {
//             if(p->weight[i]<=weight)
//             {
//                 if(p->weight[i]==weight && p->data[i]<data ||p->weight[i]<weight) 
//                 {
//                     index=i;
//                     break;
//                 } 
//                 index=i+1;
//             }
//         }
//         for(int i=p->rear+1;i>=index;i--)
//         {
//             if(i==index)
//             {
//                 p->data[i]=data;
//                 p->weight[i]=weight;
//             }
//             else
//             {
//                 p->data[i]=p->data[i-1];
//                 p->weight[i]=p->weight[i-1];
//             }
//         }
//         p->rear++;
//     printf("Data inserted\n");
//     }
// }           

// int dequeue(NODE *p)
// {
//     if(isempty(p))
//     {
//         printf("The queue is empty\n");
//         return -1;
//     }
//     else if(p->rear==p->head)
//     {
//         int value=p->data[p->rear];
//         p->rear=-1;
//         p->head=-1;
//         return value;
//     }
//     else
//         return p->data[p->head++];
// }

// void peek(NODE* p)
// {
//     if(isempty(p))
//         printf("The queue is empty\n");
//     else
//         printf("The top element is %d\n",p->data[p->head]);
// }

// void display(NODE *p)
// {
//     if(isempty(p))
//         printf("The queue is empty\n");
//     else
//     {
//         for(int i=p->head;i<=p->rear;i++)
//         {
//             if(i==p->head && i==p->rear)
//                 printf("%d --> head & rear\n",p->data[i]);
//             else if(i==p->head)
//                 printf("%d --> head\n",p->data[i]);
//             else if(i==p->rear)
//                 printf("%d -->rear\n",p->data[i]);
//             else 
//                 printf("%d -->rear\n",p->data[i]);
//         }
//     }
// }

// int main()
// {
//     int choice;
//     int value;
//     int weight;
//     NODE ans;
//     init(&ans);
//     while(1)
//     {
//         printf("1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Exit\nEnter your choice:-");
//         scanf("%d",&choice);
//         switch (choice)
//         {
//         case 1:
//             printf("Enter the value:- ");
//             scanf("%d",&value);
//             printf("Enter the weight:- ");
//             scanf("%d",&weight);
//             enqueue(&ans,value,weight);
//             break;
//         case 2:
//             value=dequeue(&ans);
//             if(value!=-1)
//                 printf("The top element is %d\n",value);
//             break;
//         case 3:
//             peek(&ans);
//             break;
//         case 4:
//             display(&ans);
//             break;
//         case 5:
//             printf("BYE BYE!!!\n");
//             return(0);
//             break;
//         default:
//             printf("Invalid choice\n");
//             break;
//         }
//     }
// }