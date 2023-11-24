#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
    struct node* last;
}NODE;

NODE* create(int value)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->next=newnode;
    newnode->last=newnode;
    newnode->data=value;
    return newnode;
}

void insert_front(NODE** start,int value)
{
    if(*start==NULL)
        *start=create(value);
    else
    {
        NODE* temp=*start;
        while(temp->next!=*start)
            temp=temp->next;
        NODE* newnode=create(value);
        newnode->next=*start;
        (*start)->last=newnode;
        temp->next=newnode;
        newnode->last=temp;
        *start=newnode;
    }
    printf("Value inserted at front\n\n");
}

void insert_back(NODE** start,int value)
{
    if(*start==NULL)
        *start=create(value);
    else 
    {
        NODE* temp=*start;
        while(temp->next!=*start)
            temp=temp->next;
        NODE* newnode=create(value);
        temp->next=newnode;
        newnode->last=temp;
        newnode->next=*start;
        (*start)->last=newnode;
    }
    printf("Value inserted at back\n\n");
}

void insert_btw(NODE** start,int value,int index)
{
    if(*start==NULL && index==0)
        insert_front(start,value);
    else if(*start==NULL)
        printf("The index if out of range\n\n");
    else if(*start!=NULL && index==0)
        insert_front(start,value);
    else 
    {
        int n=index;
        NODE* temp1=*start;
        while(index)
        {
            if(temp1==NULL)
                break;
            temp1=temp1->next;
            index--;
        }
        if(index>0)
            printf("The index is out of range\n\n");
        else if (index==0 && temp1==NULL)
        {
            insert_back(start,value);
            printf("The value %d inserted at index %d\n\n",value,n);
        }
        else 
        {
            NODE* newnode=create(value);
            newnode->last=temp1->last;
            temp1->last->next=newnode;
            newnode->next=temp1;
            temp1->last=newnode;
            printf("The value %d inserted at index %d\n\n",value,n);
        }
    }
}

void delete_front(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else 
    {
        if(*start==(*start)->next)
        {
            free(*start);
            *start=NULL;
        }
        else 
        {
            NODE* temp1=(*start)->last;
            *start=(*start)->next;
            free((*start)->last);
            (*start)->last=temp1;
            temp1->next=*start;
        }
        printf("Value deleted at front\n\n");
    }
}

void delete_back(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else 
    {
        if(*start==(*start)->next)
        {   
            free(*start);
            *start=NULL;
        }
        else
        {
            NODE* temp=*start;
            while(temp->next!=*start)
                temp=temp->next;
            temp=temp->last;
            free(temp->next);
            temp->next=*start;
            (*start)->last=temp;
        }
        printf("Value deleted at back\n\n");    
    }
}

void delete_btw(NODE** start,int index)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else if((*start)->next==*start && index==0)
    {
        printf("Value %d deleted at index %d\n\n",(*start)->data,index);
        delete_front(start);
        *start=NULL;
    }
    else 
    {        
        int n=index;
        if(index==0)
            delete_front(start);
        else
        {
            NODE* temp=*start;
            do
            {
                temp=temp->next;
                n--;
            } 
            while (temp!=*start && n-1!=0);
            if(temp==(*start)->last)
                printf("The index is out of range\n\n");
            else 
            {
                printf("Value %d deleted at index %d\n\n",temp->next->data,index);
                NODE* temp2=temp->next;
                temp->next=temp2->next;
                temp2->next->last=temp;
                free(temp2);
            }
        }
        
    }
}

void delete_all(NODE **start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* temp=*start;
        do
        {
            *start=temp->next;
            (*start)->last=temp->last;
            temp->last->next=*start;
            free(temp);
            temp=*start;
        } while (temp!=*start);
        free(temp);
        *start=NULL;
        printf("The entire list has been deleted\n\n");
    }
}

void display(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* temp=*start;
        do
        {
            printf("%d\n",temp->data);
            temp=temp->next;
        }
        while(temp!=*start);
            printf("%d--> After reverse.\n\n",temp->data);
    }
}

void reverse(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* temp=(*start)->next;
        do
        {
            (*start)->next=(*start)->last;
            (*start)->last=temp;
            if(temp->next==*start)
                break;
            *start=temp;
            temp=temp->next;
        } while (temp!=(*start)->last);
        printf("The reversed list is:-\n");
        display(start);
    }
}

void cat(NODE** start1,NODE** start2)
{
    if(*start1==NULL && *start2==NULL)
        printf("The list is empty\n\n");
    else
    {
        if(*start1==NULL) *start1=*start2;
        else if(*start2==NULL) *start2=*start1;
        else
        {
            NODE* tail1=(*start1)->last;
            NODE* tail2=(*start2)->last;
            tail1->next=*start2;(*start2)->last=tail1;
            tail2->next=*start1;(*start1)->last=tail2;
        }
        printf("The new concatinated list is:-\n");
        display(start1);
    }
}

void ordered_list(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* ptr1=*start;
        NODE* ptr2=(*start)->next;
        int count=0;
        do
        {
            ptr1=ptr1->next;
            count++;
        }
        while(ptr1!=(*start));
        int temp;
        ptr1=*start;
        for(int i=count-1;i>0;i--)
        {
            for(int j=0;j<i;j++)
            {
                if(ptr2->data<ptr1->data)
                {
                    temp=ptr2->data;
                    ptr2->data=ptr1->data;
                    ptr1->data=temp;
                }
                ptr1=ptr1->next;
                ptr2=ptr2->next;
            }
            ptr1=*start;
            ptr2=(*start)->next;
        }   
        printf("The ordered list is:-\n");
        display(start);
    }    
}

void search(NODE** start,int value)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        int count=0;
        NODE* temp=*start;
        do
        {
            if(temp->data==value)
            {
                printf("The value %d was found at index %d\n\n",temp->data,count);
                return;
            }
            count++;
            temp=temp->next;
        }
        while(temp!=*start);
        printf("%d was not found in the list\n\n",value);
    }
}

void delete(NODE **node,NODE** start)
{
    if((*node)->next==*start)
    {
        NODE* head=(*node)->last;
        free(*node);
        head->next=*start;
    }
    else
    {
        NODE* head1=(*node)->last;
        NODE* head2=(*node)->next;
        free(*node);
        head1->next=head2;
        head2->last=head1;
        head1=NULL;head2=NULL;
    }
}

void duplicate(NODE** start)
{
    if(*start==NULL)
        return;
    NODE* ptr1=*start;
    NODE* ptr2=(*start)->next;
    while(ptr1->next!=*start)
    {
        while(ptr2!=*start)
        {
            if(ptr1->data==ptr2->data)
            {
                ptr2=ptr2->last;
                delete(&ptr2->next,start);
            }
            ptr2=ptr2->next;
        }
        ptr1=ptr1->next;
        if(ptr1==NULL)
            break;
        ptr2=ptr1->next;
    }
    printf("\n");
    printf("The new list is:-\n");
    display(start);
}

int main()
{
    NODE* head=NULL;
    int choice,value,index,count;
    while(1)
    {
    printf("1.Insert front\n2.Insert middle\n3.Insert back\n4.Delete front\n5.Delete middle\n6.Delete back\n7.Delete all\n8.Display\n9.Reverse\n10.Concatinate\n11.Ordered list\n12.Duplicate remove\n13.Search\n14.Exit\nEnter your choice:-");scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                printf("\nINSERT FRONT\n");
                printf("Enter the value:-");scanf("%d",&value);
                insert_front(&head,value);
                break;
            case 2:
                printf("\nINSERT BETWEEN\n");
                printf("Enter the value:-");scanf("%d",&value);
                printf("Enter the index:-");scanf("%d",&index);
                insert_btw(&head,value,index);
                break;
            case 3:
                printf("\nINSERT BACK\n");
                printf("Enter the value:-");scanf("%d",&value);
                insert_back(&head,value);
                break;
            case 4:
                printf("\nDELETE FRONT\n");
                delete_front(&head);
                break;
            case 5:
                printf("\nDELETE BETWEEN\n");   
                printf("Enter the index:-");scanf("%d",&index);
                delete_btw(&head,index);
                break;
            case 6:
                printf("\nDELETE BACK\n");
                delete_back(&head);
                break;
            case 7:
                printf("\nDELETE ALL\n");
                delete_all(&head);
                break;
            case 8:
                printf("\nDISPLAY\n");
                display(&head);
                break;
            case 9:
                printf("\nREVERESE\n");
                reverse(&head);
                break;
            case 10:
                printf("\nCONCATINATE\n");
                NODE* head2=NULL;
                printf("Enter the no.of elements for the 2nd list:-");scanf("%d",&count);
                printf("Enter the values:-\n");
                for(int i=0;i<count;i++)
                {
                    scanf("%d",&value);
                    insert_back(&head2,value);
                }
                cat(&head,&head2);
                break;
            case 11:
                printf("\nORDERED\n");
                ordered_list(&head);
                break;
            case 12:
                printf("\nDUPLICATE ELEMENTS REMOVE\n");
                duplicate(&head);
                break;
            case 13:
                printf("\nSEARCH\n");
                printf("Enter the element to search:-");scanf("%d",&value);
                search(&head,value);
                break;
            case 14:
                printf("\nExit\n");
                printf("BYE BYE!!!\n");
                exit(0);
            default:
                printf("\nInvalid choice\n\n");
                break;
        }

    }
}


