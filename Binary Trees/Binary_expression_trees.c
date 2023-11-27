#include<stdio.h>
#include<string.h>

typedef struct node{
    char value;
    struct node* left;
    struct node* right;
}NODE;

int operator(char value)
{
    return value=='^' || value=='*' || value=='/' || value=='+' || value=='-' || value=='%';
}

NODE* create(char data)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->value=data;
    newnode->right=NULL;
    newnode->left=NULL;
    return newnode;
}

void built(char *string,NODE** root)
{
    NODE* stack[100];
    int top=-1;
    for(int i=0;i<strlen(string);i++) 
    {
        char token=string[i];
        if(!operator(token))
        {
            NODE* newnode=create(token);
            stack[++top]=newnode;
        }
        else
        {
            NODE* right=stack[top--];
            NODE* left=stack[top--];
            NODE* parent=create(token);
            parent->left=left;
            parent->right=right;
            stack[++top]=parent;
        }
    }
    *root=stack[top--];
}

int eval_expression(NODE* root)
{
    if(root==NULL)
        return 0;
    else if(!operator((root)->value))
        return root->value - '0';
    int leftnode=eval_expression(root->left);
    int rightnode=eval_expression(root->right);
    switch(root->value)
    {
        case '*':
            return leftnode*rightnode;
        case '+':
            return leftnode+rightnode;
        case '-':
            return leftnode-rightnode;
        case '^':
            return leftnode^rightnode;
        case '%':
            return leftnode%rightnode;
        case '/' :
            return leftnode/rightnode;
    }
    return 0;
}


int main()
{
    char string[100];
    printf("Enter the postfix expression to be evaluated\n");
    scanf("%s",string);
    NODE* root=NULL;
    built(string,&root);
    int result=eval_expression(root);
    printf("The evaluated expression is:- %d",result);
}


