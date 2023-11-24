#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    struct node* back;
    int data;
    struct node* next;
}NODE;

NODE* create(int value)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=value;
    newnode->next=NULL;
    newnode->back=NULL;
    return newnode;
}


void insert_front(NODE **start,int value)
{
    printf("Inserted at front.\n\n");
    if(*start==NULL)
        *start=create(value);
    else
    {
        NODE* p=*start;
        NODE* newnode=create(value);
        p->back=newnode;
        newnode->next=p;
        *start=p->back;        
    }
}

void insert_back(NODE** start,int value)
{
    printf("Inserted at back.\n\n");
    if(*start==NULL)
        *start=create(value);
    else
    {
        NODE* p=*start;
        while(p->next!=NULL)
            p=p->next;
        NODE* newnode=create(value);
        p->next=newnode;
        newnode->back=p;
    }
}

void insert_btw(NODE** start,int index,int value)
{
        NODE* p=*start;
        while(index)
        {
            if(p==NULL)
                break;
            p=p->next;
            index--;
        }
        if(p==NULL && index!=0)
            printf("The index is out of range\n\n");
        else if(p==NULL && index==0)
        {
            insert_back(start,value);
        }
        else if(index==0)
        {
            insert_front(start,value);
        }
        else
        {
            NODE* temp=p->back;
            NODE* newnode=create(value);
            temp->next=newnode;
            newnode->back=temp;
            newnode->next=p;
            p->back=newnode;
        }
}

void delete_front(NODE** start)
{
    if(*start==NULL)
        printf("The list if empty\n\n");
    else
    {
    NODE* p=*start;
    *start=p->next;
    free(p);
    if(*start!=NULL)
        (*start)->back=NULL;
    }
    printf("Deleted at front\n\n");
}

void delete_back(NODE** start)
{
    if(*start==NULL)
        printf("The list if empty\n\n");
    else
    {
        NODE* p=*start;
        while(p->next!=NULL)
            p=p->next;
        if(p->back==NULL)
        {
            free(p);
            *start=NULL;
            return;
        }
        p=p->back;
        free(p->next);
        p->next=NULL;
        printf("Deleted at back\n\n");
    }
}

void delete_btw(NODE** start,int index)
{
    if(*start==NULL)
    {
        printf("The list is empty\n\n");
        return;
    }
    NODE* p=*start;
    for(int i=0;i<index;i++)
    {
        if(p==NULL)
            break;
        p=p->next;
    }
    if(p==NULL)
    {
        printf("The index is out of range\n\n");
        return;
    }
    else if(p->back==NULL)
        delete_front(start);
    else if(p->next==NULL)
        delete_back(start);
    else
    {
        p=p->back;
        NODE* temp=p->next;
        p->next=p->next->next;
        p->next->back=p;
        printf("The deleted element is %d at index no. %d\n\n",temp->data,index);
        free(temp);
    }
}


void delete_all(NODE** start)
{
    if(*start==NULL)
        printf("The list is already empty\n\n");
    else 
    {
        while((*start)->next!=NULL)
        {
            *start=(*start)->next;
            free((*start)->back);
        }
        free(*start);
        *start=NULL;
        printf("The whole list has been deleted\n\n");
    }
}

void display(NODE** start)
{
    NODE*p =*start;
    if(p==NULL)
        printf("The list is empty\n\n");
    else
    {
        while(p!=NULL)
        {
            printf("%d\n",p->data);
            p=p->next;
        }
        printf("\n");
    }
}

void reverse(NODE** start)
{
    NODE* ptr1=*start;
    NODE* ptr2=NULL;
    if(*start==NULL)
    {
        printf("The list is empty\n\n");
        return;
    }
    ptr2=ptr1->next;
    ptr1->next=NULL;
    ptr1->back=ptr2;
    while(ptr2!=NULL)
    {
        ptr2->back=ptr2->next;
        ptr2->next=ptr1;
        ptr1=ptr2;
        ptr2=ptr2->back;
    }
    *start=ptr1;
    printf("The revered list is:-\n");
    display(start);
}

void cat(NODE** start1,NODE** start2)
{
    if(*start1==NULL && *start2==NULL) printf("The lists are empty\n\n"); 
    else if(*start1==NULL) *start1=*start2;
    else if(*start2==NULL) *start2=*start1;
    else
    {
        NODE*p1=*start1;
        NODE*p2=*start2;
        while(p1->next!=NULL)
            p1=p1->next;
        p1->next=p2;
        p2->back=p1;
    }
}

void ordered(NODE** start)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        NODE* ptr1=*start;
        NODE* ptr2=(*start)->next;
        int count=0;
        while(ptr1!=NULL)
        {
            ptr1=ptr1->next;
            count++;
        }
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
            ptr1=ptr1->next;
            n++;
        }
        ptr1=head;
        int arr[n],count=0;
        int trav=n/2;
        for(int i=0;i<trav;i++)
        {
            for(int j=0;j<i;j++)
                ptr1=ptr1->next;
            for(int k=n-1-i;k>0;k--)
                ptr2=ptr2->next;
            arr[count]=ptr1->data;
            arr[count+1]=ptr2->data;
            count=count+2;
            ptr1=head;
            ptr2=head;
        }
        if(n%2!=0)
        {
            for(int i=0;i<n/2;i++)
                ptr1=ptr1->next;
            arr[count]=ptr1->data;
        }
        for(int i=0;i<n;i++)
        {
            head->data=arr[i];
            head=head->next;
        }
    }
    printf("The reordered list is:-\n");

}

void delete(NODE **node)
{
    if((*node)->next==NULL)
    {
        NODE* head=(*node)->back;
        free(*node);
        head->next=NULL;
    }
    else
    {
        NODE* head1=(*node)->back;
        NODE* head2=(*node)->next;
        free(*node);
        head1->next=head2;
        head2->back=head1;
        head1=NULL;head2=NULL;
    }
}

void remove_dup(NODE** start)
{
    if(*start==NULL)
        return;
    NODE* ptr1=*start;
    NODE* ptr2=(*start)->next;
    while(ptr1->next!=NULL)
    {
        while(ptr2!=NULL)
        {
            if(ptr1->data==ptr2->data)
            {
                ptr2=ptr2->back;
                delete(&ptr2->next);
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

void search(NODE** start,int value)
{
    if(*start==NULL)
        printf("The list is empty\n\n");
    else
    {
        int count=0;
        NODE* temp=*start;
        while(temp!=NULL)
        {
            if(temp->data==value)
            {
                printf("The value %d was found at index %d\n\n",temp->data,count);
                return;
            }
            count++;
            temp=temp->next;
        }
        printf("%d was not found in the list\n\n",value);
    }
}


int main()
{
    NODE* head=NULL;
    int cond;
    int value,index;
    while(1)
    {
    printf("1.Insert front\n2.Insert middle\n3.Insert back\n4.Delete front\n5.Delete middle\n6.Delete back\n7.Delete all\n8.Display\n9.Reverse\n10.Concatinate\n11.Ordered list\n12.Reorder\n13.Duplicate remove\n14.Search\n15.Exit\n");
    printf("Enter your choice:-");scanf("%d",&cond);printf("\n");
        switch (cond)
        {
            case 1 :
                printf("INSERT FRONT\n");
                printf("Enter the value of node:-");scanf("%d",&value);
                insert_front(&head,value);
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
                break;
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
                    insert_back(&head2,value);   
                }
                cat(&head,&head2);
                break;
            case 11:
                printf("ORDERED LIST\n");
                ordered(&head);
                break;
            case 12:
                printf("REORDER\n");
                reorderList(head);
                display(&head);
                break;
            case 13:
                printf("REMOVE DUPLICATES\n");
                remove_dup(&head);
                break;
            case 14:
                printf("SEARCH\n");
                printf("Enter the value to search:-");scanf("%d",&value);
                search(&head,value);
                break;
            case 15:
                printf("BYE BYE!!!\n");
                return 0;
            default:
                printf("Invaild size\n");
                break;
        }   
    }
}





