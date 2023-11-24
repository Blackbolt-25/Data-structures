#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}NODE;

NODE* create(int value)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=value;
    newnode->next=newnode;
    return newnode;
}

void insert_front(NODE** start,int value)
{
    NODE* newnode=create(value);
    if(*start==NULL)
        *start=newnode;
    else
    {
        NODE* temp=*start;
        while(temp->next!=*start)
            temp=temp->next;
        newnode->next=*start;
        temp->next=newnode;
        *start=newnode;
    }
    printf("Value inserted at front\n\n");
}

void insert_btw(NODE** start,int value,int index)
{
    if(*start==NULL && index==0)
        insert_front(start,value);
    else if(*start==NULL)
        printf("The index is out of range\n\n");
    else
    {
        NODE* p=*start;
        int n=index,n1=index;
        do
        {
            p=p->next;
            index--;
        }
        while(p!=*start && index!=0);
        if(index>0)
            printf("Index is out of range\n\n");
        else if(index<0)
        insert_front(start,value);
        else
        {
            NODE* temp=*start;
            while(temp->next!=p)
                temp=temp->next;
            NODE* newnode=create(value);
            newnode->next=p;
            temp->next=newnode;
            printf("%d value inserted at index %d\n\n",value,n1);
        }

    }
}

void insert_back(NODE** start,int value)
{   
    NODE* newnode=create(value);
    if(*start==NULL)
        *start=newnode;
    else
    {
        NODE* temp=*start;
        while(temp->next!=*start)
            temp=temp->next;
        temp->next=newnode;
        newnode->next=*start;
    }
    printf("Value inserted at back\n\n");
}


void delete_front(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else if(*start==(*start)->next)
    {
        free(*start);
        *start=NULL;
        printf("Value deleted from front\n\n");
    }
    else
    {
        NODE* p=*start;
        while(p->next!=*start)
            p=p->next;
        p->next=(*start)->next;
        p=*start;
        *start=p->next;
        free(p);
        printf("Value deleted from front\n\n");
    }
}

void delete_btw(NODE** start,int index)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        int n=index-1,n1=index;
        NODE* p=*start;
        do
        {
            p=p->next;
            n--;
        }
        while(n!=0 && p!=*start);
        if(n<0)
        {
            if(index==1 && p->next==p)
                printf("Index is out of range\n\n");
            else if(index==1)
            {
                printf("%d is deleted at index %d\n\n",p->next->data,1);
                p=p->next;
                (*start)->next=(*start)->next->next;
                free(p);
            }
            else if(*start==p && p->next==p)
            {
                printf("%d is deleted at index %d\n\n",p->data,0);
                free(*start);
                *start=NULL;
            }
            else 
            {
                printf("%d is deleted at index %d\n\n",p->data,0);
                NODE* temp=*start;
                while(temp->next!=*start)
                    temp=temp->next;
                *start=(*start)->next;
                temp->next=*start;
                free(p);
            }
        }
        else if(n>0 || p->next==*start || p==*start) 
            printf("Index is out of range\n\n");
        else
        {
            printf("%d is deleted at index %d\n\n",p->next->data,n1);
            NODE* temp=p->next->next;
            free(p->next);
            p->next=temp;
        }
    }
}

void delete_back(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else if(*start==(*start)->next)
    {
        free(*start);
        *start=NULL;
        printf("Value deleted from back\n\n");
    }
    else
    {
        NODE *p=*start;
        while(p->next->next!=*start)
            p=p->next;
        free(p->next);
        p->next=*start;
        printf("Value deleted from back\n\n");
    }
}


void display(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else if(*start==(*start)->next)
    {
        printf("%d\n%d--> After reverse.\n",(*start)->data,(*start)->next->data);
    }
    else
    {
        NODE* p=*start;int count=0;
        while(p!=(*start)->next || count!=1)
        {
            if(count==0 && p==(*start)->next)
            {
                printf("%d\n",p->data);
                count++;
            }
            else if(count==1 && p==*start)
                printf("%d--> After reverse.\n",p->data);
            else
                printf("%d\n",p->data);
            p=p->next;
        }
    }
    printf("\n");
}


void reverse(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* back=*start;
        while(back->next!=*start)
            back=back->next;
        NODE* current=*start;
        NODE* link=(*start)->next;
        while(link!=*start)
        {
            current->next=back;
            back=current;
            current=link;
            link=link->next;
        }
        current->next=back;
        *start=current;
        current=NULL;back=NULL;link=NULL;
        printf("The reversed list is :-\n");
        display(start);
    }
}

void delete_all(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* temp1=*start;
        NODE* temp2=*start;
        while(temp2->next!=*start)
            temp2=temp2->next;
        while(temp1!=temp2)
        {
            *start=(*start)->next;
            free(temp1);
            temp1=*start;
        }
        free(*start);
        *start=NULL;
        temp1=NULL;
        temp2=NULL;
        printf("The entire list has been deleted\n\n");
    }
}

void cat(NODE** start1,NODE** start2)
{
    if(*start1==NULL) *start1=*start2;else if(*start2==NULL) *start2=*start1;
    else
    {
        NODE* temp1=*start1;
        NODE* temp2=*start2;
        while(temp1->next!=*start1)
            temp1=temp1->next;
        while(temp2->next!=*start2)
            temp2=temp2->next;
        temp1->next=*start2;
        temp2->next=*start1;
    }
    printf("The concatinated list is:-\n");display(start1);
}

void ordered_list(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else 
    {
        NODE* temp1=*start;
        NODE* temp2=(*start)->next;
        while(temp1->next!=*start)
        {
            while(temp2!=*start)
            {
                if(temp2->data<temp1->data)
                {
                    int temp=temp1->data;
                    temp1->data=temp2->data;
                    temp2->data=temp;
                }
                temp2=temp2->next;
            }
            temp1=temp1->next;
            temp2=temp1->next;
        }
        printf("The ordered list is:-\n");
        display(start);
    }   
}

void duplicate(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* head1=*start;
        NODE* head2=*start;
        do
        {
            while(head2->next!=*start)
            {
                if(head1->data==head2->next->data)
                {
                    if(head2->next->next==*start)
                    {
                        free(head2->next);
                        head2->next=*start;
                        break;
                    }
                    else
                    {
                        NODE* temp=head2->next->next;
                        free(head2->next);
                        head2->next=temp;
                    }
                }
                head2=head2->next;
            }
            head1=head1->next;
            head2=head1;
        }
        while(head1!=*start);
        printf("The new list is:-\n");
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
                printf("\nDISPLAY\n");
                display(&head);
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