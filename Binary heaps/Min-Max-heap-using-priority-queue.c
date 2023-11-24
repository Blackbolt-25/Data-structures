// Implementation of Priority queue using min-max heap
//
//Note:- Priority queue can be implemented using either array or heap data structure or both.
//Drawbacks of P-Q implementation using arrays
//  i) Consumes a lot of time during shift operations.
//Advantages of priority queue implementation using heap
//i) insertion and accessiong will be faster if we use head DS.


#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    int weight;
}NODE;

typedef struct pq{
    NODE* pq;
    int size;
    int capacity;
}PQ;


PQ* create_pq(int c)
{
    PQ* p_q= (PQ*)malloc(sizeof(PQ));
    p_q->pq=(NODE*)malloc(sizeof(NODE)*c);
    p_q->size=0;
    p_q->capacity=c;
    return p_q;
}

void swap(NODE* a,NODE*b)
{
    int temp;
    temp=a->data;
    a->data=b->data;
    b->data=temp;
    temp=a->weight;
    a->weight=b->weight;
    b->weight=temp;
}

void enqueue(PQ* p_q,int data,int weight)
{
    if(p_q->size >= p_q->capacity)
    {
        printf("Priority queue overflow\n");
        return; 
    }
    p_q->pq[p_q->size].data=data;
    p_q->pq[p_q->size].weight=weight;
    int current=p_q->size++;
    while(current>0 && p_q->pq[current].weight > p_q->pq[(current-1)/2].weight)
    {
        swap(&p_q->pq[current],&p_q->pq[(current-1)/2]);
        current=(current-1)/2;
    }
    printf("Data inserted successfully\n");
}


void max_heapify(PQ *p_q,int index)
{
    int current=index;        
    int left_child=2*index+1;
    int right_child=2*index+2;
    if(current<p_q->capacity && p_q->pq[current].weight<p_q->pq[left_child].weight)
          current = left_child;
    if(current<p_q->capacity && p_q->pq[current].weight<p_q->pq[right_child].weight)
          current= right_child;
    if(current!=index)
    {
        swap(&p_q->pq[current],&p_q->pq[index]);
        max_heapify(p_q,current);
    }
}

void display_p_q(PQ *p_q)
{
    if(p_q->size==0)
          printf("The queue is empty\n");
    else
    {
        printf("The queue in :-\n");
        for(int i=0;i<p_q->size;i++)
             printf("%d ",p_q->pq[i].data);
        printf("\n");
    }
}

int dequeue(PQ * p_q)
{ 
    if(p_q->size<=0)
        return -1;
    else if(p_q->size==1)
    {
        p_q->size--;
        return p_q->pq[0].data;
    }
    int temp=p_q->pq[0].data; 
    p_q->pq[0].data=p_q->pq[p_q->size-1].data;
    p_q->pq[0].weight=p_q->pq[p_q->size-1].weight;
    p_q->size--;
    max_heapify(p_q,0);
    return temp;
}

int main()
{ 
    int c;    
    printf("Enter the capacity of the priority queue:-\n");
    scanf("%d",&c);
    PQ* p_q;
    p_q=create_pq(c);
    int choice;
    int value=0;
    int w=0;
    while(1)
    {
        printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\nEnter the choice:-");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter the value:-\n");
                scanf("%d",&value); 
                printf("Enter the weight:-\n");
                scanf("%d",&w);
                enqueue(p_q,value,w);
                break;
            case 2:
                value=dequeue(p_q);
                if(value==-1)
                    printf("The given priority_queue is empty\n");
                else
                    printf("The max value is:- %d\n",value);
                break;
            case 3:
                display_p_q(p_q);                                           
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

