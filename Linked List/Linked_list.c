// Linked list

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void insert_front(int value,NODE **start)
{
    struct node *temp=create_node(value);
    temp->link=*start;
    *start=temp;
}


void insert_btw(NODE **start,int n,int value)
{
    if(*start==NULL && n==0)
    {
        *start=create_node(value);
        printf("Data inserted\n");
    }
    else if(*start==NULL)
        printf("The link list is empty\n");
    else
    {
        NODE* p=*start;
        for(int i=0;i<n-1;i++)
            p=p->link;
        if(p==NULL)
        {
            printf("The value of index is too high\n");
            return;
        }
        NODE* newnode=create_node(value);
        if(n==0)
        {
            newnode->link=*start;
            *start=newnode;
            printf("Data inserted in btw\n");
            return;
        }
        newnode->link=p->link;
        p->link=newnode;
        printf("Data inserted in btw\n");
    }
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

void delete_front(NODE ** start)
{
    struct node *temp;
    int value;
    if(*start==NULL)
        printf("The linked list is empty.\n");
    else
    {
        temp=*start;
        *start=(*start)->link;
        printf("The deleted element is %d\n",temp->data);
        free(temp);
        return;
    }
}

void delete_btw(NODE **start,int n)
{
    if(*start==NULL)
    {
        printf("The Linked list is empty.\n");
        return;
    }
    else 
    {
        NODE* p=*start;
        for(int i=0;i<n-1;i++)
        {
            if(p==NULL)
            {
                break;
            }
            p=p->link;
        }
        if(p==NULL)
        {
            printf("Invalid index\n");
            return;
        }
        else if(p->link==NULL && n!=0)
        {
            printf("Invalid index\n");
            return;
        }
        NODE* temp=p->link;
        if(n==0)
        {
            *start=p->link;
            printf("The data deleted is %d at index no. %d\n",p->data,n);
            free(p);
            return;
        }
        p->link=p->link->link;
        free(temp);
        printf("The data deleted is %d at index no. %d\n",p->data,n);
    }
}

void delete_back(NODE **start)
{
    if(*start==NULL)
    {
        printf("The Linked list is empty.\n");
        return;
    }
    else if((*start)->link==NULL)
    {
        free(*start);
        *start=NULL;
        printf("Data deleted succesfully.\n");
        return;
    }
    NODE* temp=*start;
    while(temp->link->link!=NULL)
        temp=temp->link;
    free(temp->link);
    temp->link=NULL;
    printf("Data deleted succesfully.\n");
}


void display(NODE** start)
{
    if(*start==NULL)
        printf("The Linked list is empty.\n");
    NODE* temp;
    temp=*start;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->link;
    }
}

void reverse(NODE **start)
{
    if(*start==NULL)
    {
        int value;
        printf("Enter the value:-");scanf("%d",&value);
        insert_front(value,start);
    }
    else
    {
        NODE* next,*prev=NULL;
        while(*start)
        {
            next=(*start)->link;
            (*start)->link=prev;
            prev=*start;
            *start=next;
        }
        *start=prev;
        display(start);
    }
}

void cat(NODE** start1,NODE** start2)
{
    if(*start1==NULL && *start2==NULL)
    {
        printf("Both are empty\n");
        return;
    }
    else if(*start1==NULL)
    {
        printf("The conatinated list is:-\n");
        *start1=*start2;
        display(start1);
        return;
    }
    printf("The conatinated list is:-\n");
    NODE* temp1=*start1;
    while(temp1->link!=NULL)
        temp1=temp1->link;
    NODE* temp2=*start2;
    temp1->link=temp2;
    display(start1);
}

void delete_all(NODE** start)
{
    NODE* temp=*start;
    while(temp!=NULL)
    {
        *start=temp->link;
        free(temp);
        temp=*start;
    }
    printf("All elements are deleted\n");
}

void ordered(NODE** start)
{
    if(*start==NULL)
    {
        printf("List is empty\n");
        return;
    }
    NODE* temp1=*start;
    NODE* temp2=temp1->link;
    int temp;
    while(temp1->link!=NULL)
    {
        while(temp2->link!=NULL)
        {
            temp2=temp2->link;
            if(temp2->data<temp1->data)
            {
                temp=temp1->data;
                temp1->data=temp2->data;
                temp2->data=temp;
            }
        }
        temp1=temp1->link;
        temp2=temp1->link;
    }
    printf("The ordered list is:-\n");
    display(start);
}

void reorderList(NODE* head){
    if(head==NULL)
        return;
    else
    {
        int n=0;
        NODE* ptr1=head;
        NODE* ptr2=head;
        while(ptr1!=NULL)
        {
            ptr1=ptr1->link;
            n++;
        }
        ptr1=head;
        int arr[n],count=0;
        int trav=n/2;
        for(int i=0;i<trav;i++)
        {
            for(int j=0;j<i;j++)
                ptr1=ptr1->link;
            for(int k=n-1-i;k>0;k--)
                ptr2=ptr2->link;
            arr[count]=ptr1->data;
            arr[count+1]=ptr2->data;
            count=count+2;
            ptr1=head;
            ptr2=head;
        }
        if(n%2!=0)
        {
            for(int i=0;i<n/2;i++)
                ptr1=ptr1->link;
            arr[count]=ptr1->data;
        }
        for(int i=0;i<n;i++)
        {
            head->data=arr[i];
            head=head->link;
        }
    }
    printf("The reordered list is:-\n");

}

int main()
{
    NODE* head=NULL;
    int cond;
    int value,index;
    while(1)
    {
    printf("1.Insert front\n2.Insert middle\n3.Insert back\n4.Delete front\n5.Delete middle\n6.Delete back\n7.Delete all\n8.Display\n9.Reverse\n10.Concatinate\n11.Ordered list\n12.Reorder\n13.Exit\n");
    printf("Enter your choice:-");scanf("%d",&cond);
        switch (cond)
        {
            case 1 :
                printf("INSERT FRONT\n");
                printf("Enter the value of node:-");scanf("%d",&value);
                insert_front(value,&head);
                printf("Inserted at front.\n");
                break;
            case 2:
                printf("INSERT MIDDLE\n");
                printf("Enter the value of node:-");scanf("%d",&value);
                printf("Enter the index value:-");scanf("%d",&index);
                insert_btw(&head,index,value);
                break;
            case 3:
                printf("INSERT BACK\n");
                printf("Enter the value of node:-");scanf("%d",&value);
                insert_back(&head,value);
                printf("Inserted at back.\n");
                break;
            case 4:
                printf("DELETE FRONT\n");
                delete_front(&head);
                break;
            case 5:
                printf("DELETE MIDDLE\n");
                printf("Enter the index value:-");scanf("%d",&index);
                delete_btw(&head,index);
                break;
            case 6:
                printf("DELETE back\n");
                delete_back(&head);
                break;
            case 7:
                printf("DELETE ALL\n");
                delete_all(&head);
            case 8: 
                printf("DISPLAY\n");
                display(&head);
                break;
            case 9:
                printf("REVERSE\n");
                reverse(&head);
                break;
            case 10:
                printf("Concatinate\n");int len;
                printf("Enter the len of 2nd list\n");
                scanf("%d",&len);
                NODE* head2=NULL;
                for(int i=0;i<len;i++)
                {
                    printf("Enter value %d:- ",i+1);scanf("%d",&value);
                    insert_front(value,&head2);   
                }
                cat(&head,&head2);
                break;
            case 11:
                ordered(&head);
                break;
            case 12:
                printf("REORDER\n");
                reorderList(head);
                display(&head);
                break;
            case 13:
                printf("BYE BYE!!!\n");
                return 0;
            default:
                printf("Invaild size\n");
                break;
        }   
    }
}

void ordered(NODE* start)
{
    if(start==NULL)
        return;
    else
    {
        NODE* ptr1=start->link;
        NODE* ptr2=start;
        int n;
        while(ptr2->link->link!=NULL)
        {
            ptr2=ptr2->link;
            n++;
        }
        n=n+2;
        while(ptr1->link->link!=NULL)
        {
            int temp;
            temp=ptr1->data;
            ptr1->data=ptr1->link->data;
            ptr1->link->data=temp;
            temp=ptr2->link->data;
            ptr2->link->data=ptr1->data;
            ptr1->data=temp;
            ptr1=ptr1->link;
            if(ptr1->link->link==NULL)
                break;
            temp=ptr2->data;
            ptr2->data=ptr2->link->data;
            ptr2->link->data=temp;
        }


    }
}




