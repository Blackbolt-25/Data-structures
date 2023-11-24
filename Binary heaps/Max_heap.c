#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100


typedef struct heap{
    int *arr;
    int size;
    int capacity;
}HEAP;


void init(HEAP **newheap,int c)
{
    *newheap=(HEAP*)malloc(sizeof(HEAP));
    (*newheap)->arr=(int*)malloc(sizeof(int)*c);
    (*newheap)->size=0;
    (*newheap)->capacity=c;
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void max_heapify(HEAP* root,int i)
{
    int largest=i;
    int lc=2*i+1;
    int rc=2*i+2;
    if(root->size>i && root->arr[largest]<root->arr[lc])
        largest=lc;
    if(root->size>i && root->arr[largest]<root->arr[rc])
        largest=rc;
    if(largest!=i)
    {
        swap(&root->arr[i],&root->arr[largest]);
        max_heapify(root,largest);
    }
}

void insert(HEAP* root,int value)
{
    if(root->size>=root->capacity)
        printf("Heap overflow"); 
    else
    {
        root->arr[root->size++]=value;
        int current_index=root->size-1;
        while(current_index>0 && root->arr[current_index]>root->arr[(current_index-1)/2])
        {
            swap(&root->arr[current_index],&root->arr[(current_index-1)/2]);
            current_index=(current_index-1)/2;
        }
        printf("The value has been inserted successfully\n");
    }
}


int extract_max(HEAP* root)
{
    if(root->size<=0)
        return -1;
    int temp=root->arr[0];
    root->arr[0]=root->arr[--root->size]; 
    max_heapify(root,0); 
    return temp;
}

void display(HEAP *root)
{
    if(root->size<=0)
        printf("The given heap is empty\n");
    else
    {
        printf("The given heap is :-\n");
        for(int i=0;i<root->size;i++)
            printf("%d ",root->arr[i]);
        printf("\n");
    }
}

int main()
{
    int c;
    printf("Enter the capacity of the max_heap: ");
    scanf("%d",&c);
    HEAP* heap=NULL;
    init(&heap,c);
    int choice;
    int value;
    while(1)
    {
        printf("1.Insert\n2.Extract Max element\n3.Display\n4.Exit\nEnter you choice:-");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter the value to be inserted:- ");
                scanf("%d",&value);  
                insert(heap,value);
                break;
            case 2:    
                value=extract_max(heap);
                if(value==-1)
                    printf("The given heap is empty\n");
                else
                    printf("The max element is:- %d\n",value);
                break; 
            case 3:
                display(heap);
                break;
            case 4:
                printf("BYE BYE\n");
                return 0;
            case 5:
                printf("Invalid choice\n");
                break;
        }
    }
}










