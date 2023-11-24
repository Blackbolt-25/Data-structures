#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    int height;
}NODE;

NODE* create(int value)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=value;
    newnode->right=NULL;
    newnode->left=NULL;
    newnode->height=0;
    return newnode;
}

int height(NODE* root)
{
    if(root==NULL)
        return 0;
    return root->height;
}

int max(int a,int b)
{
    return a>b ? a : b;
}

NODE* left_rotate(NODE* x)
{
    NODE* y=x->left;
    NODE* T2=y->left;

    y->left=x;
    x->right=T2;

    y->height= 1+max(height(y->left),height(y->right));
    x->height= 1+max(height(x->left),height(x->right));

    return y;
}

NODE* right_rotate(NODE* y)
{
    NODE* x=y->left;
    NODE* T1=x->right;

    x->right=y;
    y->left=T1;

    x->height = 1+max(height(x->left),height(x->right));
    y->height = 1+max(height(y->left),height(y->right));

    return x;
}


int Balance_factor(NODE* root)
{
    if(root==NULL)
        return 0;
    return height(root->left)-height(root->right);
}

NODE* insert(NODE* root,int data)
{
    if(root==NULL)      //Imp to give only the NULL cond. if and the rest if,else if and else.
    {
        NODE* newnode=create(data);
        return newnode;
    }
    if(data<root->data)
        root->left=insert(root->left,data);
    else if(data>root->data)
        root->right=insert(root->right,data);
    else
        return root;

    root->height= 1+ max(height(root->right),height(root->left));
    int balance=Balance_factor(root);
    if(balance > 1 && root->left->data > data)
        return right_rotate(root);
    if(balance < -1 && root->right->data < data)
        return left_rotate(root);
    if(balance > 1 && root->left->data < data)
    {
        root->left=left_rotate(root->left);
        return right_rotate(root);
    }
    if(balance < -1 && root->left->data > data)
    {
        root->right=right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}


void inorder(NODE* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
} 


int main()
{
    NODE* root=NULL;
    printf("Enter the root element:- ");
    int value;
    scanf("%d",&value);
    root=insert(root,value);
    int count;
    printf("Enter the no.of elements to be inserted:- ");
    scanf("%d",&count);
    for(int i=0;i<count;i++)
    {
        printf("Enter the element:- ");
        scanf("%d",&value);
        root=insert(root,value);
    }
    printf("The inorder traversal of elements is:-\n");
    inorder(root);
}
