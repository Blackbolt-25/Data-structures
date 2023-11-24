#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct node{
    int * harr;
    int capacity;
    int size;
}NODE;

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
    
int parent(int i)
{
    return floor(i-1) /2;
}


NODE* create_minHeap(int c)
{
    NODE* heap;
    heap=(NODE*)malloc(sizeof(NODE));
    heap->harr = (int *)malloc(sizeof(int) * c);
    heap->capacity = c;
    heap->size = 0;
    return heap;
}

void heapify(NODE* root,int index)
{
    int smallest=index;
    int left=2*index+1;
    int right=2*index+2;
    if(left<root->size && root->harr[left]<root->harr[smallest])
        smallest=left;
    if(right<root->size && root->harr[right]<root->harr[smallest])
        smallest=right;
    if(smallest!=index)
    {
        swap(&root->harr[smallest],&root->harr[index]);
        heapify(root,smallest);
    }
}

void insert(int value,NODE** heap)
{
    if((*heap)->size>=(*heap)->capacity)
        printf("Heap overflow\n");
    else
    {
        (*heap)->harr[(*heap)->size]=value;
        int current_index=(*heap)->size;
        (*heap)->size++;
        while(current_index>0 && (*heap)->harr[current_index]<(*heap)->harr[parent(current_index)])
        {
            swap(&(*heap)->harr[current_index],&(*heap)->harr[parent(current_index)]);
            current_index=parent(current_index);
        }
    }
}

int extract_min(NODE** heap)
{
    if((*heap)->size<=0)
        return -1;
    int temp=(*heap)->harr[0];
    (*heap)->harr[0]=(*heap)->harr[--(*heap)->size];
    heapify(*heap,0);
    return temp;
}


void inorder_display(NODE* heap)
{
    if(heap->size==0)
        printf("The given heap is empty\n");
    else
    {
        printf("The inorder display of the heap is:-\n");
        for (int i = 0; i < heap->size; i++)
            printf("%d ", heap->harr[i]);
        printf("\n");
    }
}


int main()
{
    int c;
    printf("Enter the capacity for the heap:-");
    scanf("%d",&c);
    NODE* heap=create_minHeap(c);
    int choice;
    while(1)
    {
        printf("1.Insert\n2.Extract minimum\n3.Inorder display\n4.Exit\nEnter choice:-");
        scanf("%d", &choice);
        int value;
        switch (choice)
        {
            case 1:
                printf("Enter the value to be inserted:-");
                scanf("%d",&value);
                insert(value,&heap);
                break;
            case 2:
                value=extract_min(&heap);
                if(value==-1)
                    printf("The given heap is empty\n");
                else
                    printf("The minimun value is:- %d\n", value);
                break;
            case 3:
                inorder_display(heap);
                break;
            case 4:
                printf("Bye Bye!!!\n");
                return 0;
            default:
                printf("Invalid case\n");
                break;
        }
    }
}
