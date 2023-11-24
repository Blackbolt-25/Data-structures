#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* right;
    struct node* left;
}NODE;

void create(int root_val,NODE** p)
{
    (*p)=(NODE*)malloc(sizeof(NODE));
    (*p)->data=root_val;
    (*p)->left=NULL;
    (*p)->right=NULL;
}   

void insert(int value,NODE *p)
{
    if(p==NULL)
        create(value,&p);
    else if(p->data>value)
        insert(value,p->right);
    else if(p->data<value)
        insert(value,p->left);
    else
    {
        printf("The value entered is equal to an element already inside the tree.\nPls enter a value > or < than %d.\n",value);
        return;
    }

}

NODE* delete(NODE* root,int value)
{
    if(root==NULL)
        return root;
    else if(root->data>value)
    {
        root->left=delete(root->left,value);
        return root;
    }
    else if(root->data<value)
    {
        root->right=delete(root->right,value);
        return root;
    }
    else if(root->right==NULL && root->left==NULL) //If node has no children
    {
        free(root);
        return NULL;
    }
    else if(root->right==NULL) //If Node has only one child.
    {
        NODE* temp=root->left;
        free(root);
        return temp;
    }
    else if(root->left==NULL) //If Node has only one child.
    {
        NODE* temp=root->right;
        free(root);
        return temp;
    }
    else                    //If Node has two children.
    {
        NODE* succ_parent=root;
        NODE* succ=root->right;
        while(succ->left!=NULL)
        {
            succ_parent=succ;
            succ=succ->left;
        }
        if(succ_parent!=root)
            succ_parent->left=succ->right;
        else 
            succ_parent->right=succ->right;
        root->data=succ->data;
        free(succ);
        return root;
    }
}


int height(NODE* root)
{
    if(root==NULL)
        return 0;
    else 
    {
        int l_depth=height(root->left);
        int r_depth=height(root->right);
        if(l_depth>r_depth)
            return l_depth+1;
        else 
            return r_depth+1;
    }
}


void inorder(NODE* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void postorder(NODE* root)
{
    if(root==NULL)
        return;
    printf("%d ",root->data);
    inorder(root->left);
    inorder(root->right);
}

void preorder(NODE* root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    inorder(root->right);
    printf("%d ",root->data);
}


int search(NODE* root,int value)
{
    if(root==NULL)
        return 0;
    else if(root->data==value)
        return 1; 
    int cond=search(root->left,value);
    if(cond!=0)
        return cond;
    cond=search(root->right,value);
    return cond;
}

int main()
{
    NODE *root;
    int root_val,choice=1,value;
    printf("Enter the value of root node:- ");
    scanf("%d",&root_val);
    create(root_val,&root);
    while(choice)
    {
        printf("Enter the value to be entered:- ");scanf("%d",&value);
        insert(value,root);
        printf("Do you want to enter a value again? :- \n");
        scanf("%d",&choice);
    }   
    printf("Do you want to delete values entered? :- ");
    scanf("%d",&choice);
    while(choice)
    {
        printf("Enter the value to be deleted:- ");scanf("%d",&value);
        delete(root,value);
        printf("Do you want to delete a value again? :- \n");
        scanf("%d",&choice);
    }
    int height_max=height(root);
    printf("The height of the value:- %d\n",height_max);
    printf("Inorder:-\n");
    inorder(root);
    printf("\n");
    printf("Preorder\n");
    preorder(root);
    printf("\n");
    printf("Postorder\n");
    postorder(root);
    printf("\n");
}
