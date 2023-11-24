#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    char data;
    struct tree* right;
    struct tree* left;
    int isr_t;
    int isl_t;
}T_TREE;

T_TREE* create(char data)
{
    T_TREE* newnode=(T_TREE*)malloc(sizeof(T_TREE));
    newnode->right=NULL;
    newnode->left=NULL;
    newnode->isr_t=1;
    newnode->isl_t=1;
    return newnode;
}

void init(T_TREE** root,char data)
{
    T_TREE* dummy=create('D');
    (*root)=create(data);
    (*root)->left=dummy;
    (*root)->right=dummy;
    dummy->right=*root;
    dummy->left=dummy;
}

void insert(T_TREE* root,char data)
{
    T_TREE *current=root;  
    T_TREE *newnode=create(data);
    while(current)
    {
        if(data<current->data)
        {
            if(current->isl_t)
            {
                newnode->left=current->left;
                newnode->right=current;
                current->left=newnode;
                current->isl_t=0;
                return;
            }
            current=current->left;
        }
        else
        {
            newnode->right=current->right;
            newnode->left=current;
            current->right=newnode;
            current->isr_t=0;
            return;
        }
        current=current->right;
    }
}


T_TREE* leftmost(T_TREE* root)
{
    while(root->isl_t!=1)
        root=root->left;
    return root;
}


void display_preorder_threaded(T_TREE* root)
{
    printf("%c ",root->data);
    if(!root->isl_t)
        display_preorder_threaded(root->left);
    if(!root->isr_t)
        display_preorder_threaded(root->right);
}


void display_postorder_threaded(T_TREE* root)
{
    if(!root->isl_t)
        display_postorder_threaded(root->left);
    if(!root->isr_t)
        display_postorder_threaded(root->right);
    printf("%c ",root->data);
}

int height(T_TREE* root)
{
    if(root->isl_t && root->isr_t)
        return 0;
    else
    {
        int l_depth=0;
        int r_depth=0;
        if(root->isl_t)
            return 1;
        else
            l_depth=height(root->left);
        if(root->isr_t)
            return 1;
        else  
            r_depth=height(root->right);
        return (l_depth)>(r_depth)? l_depth+1 : r_depth+1;
    }
}



//Using Morris inorder Traversal method coz its the most efficient as it does not use stack or recursion.
char predecessor(char value,T_TREE* node)
{
    T_TREE* ans;
    while(node)  
    {
        if(node->data==value)       //Data is found.
        {
            ans=node->left;
            if(node->isl_t)         // If the targets left child (ans) has no right child then its left childs data is the predecessor.  
                return ans->data;
            else                    //If the left child has a right chlild, then find the right decendent of the left node (ans) coz that the predecessor. 
            {
                while(!ans->isr_t)
                    ans=ans->right;
                return ans->data;
            }
        }
        else if(node->data<value && !node->isl_t)
            node=node->left;
        else if(node->data>value && !node->isr_t)
            node=node->right;
        else                      //If data is not found then return a dummy value.
            return 'D';
    }
    return 'D';
}

char successor(char value,T_TREE* node)
{
    T_TREE* ans;
    while(ans)
    {
        if(node->data==value)       //Data is found.      
        {
            ans=node->right;        
            if(node->isr_t)         // If the targets right child (ans) has no left child then the left childs data (ans->data) is the successor.
                return ans->data;
            else                    // If the targets right child (ans) has left decendents then find the left-most decendent coz thats the successor.
            {
                while(!ans->isl_t)
                    ans=ans->left;
                return ans->data;
            }
        }
        else if(node->data<value && !node->isl_t)
            node=node->left;
        else if(node->data>value && !node->isr_t)
            node=node->right;
        else                       //If data is not found then return a dummy value. 
            return 'D';
    }
    return 'D';
}


void display_inorder_threaded(T_TREE* root)
{
    T_TREE* temp=leftmost(root);
    char var=temp->data;
    while(var!='D')    
    {
        printf("%c ",temp->data);
        var=successor(var,root);
    }
    printf("\n");
}


int main()
{
    T_TREE *root=NULL;
    int data;
    printf("Enter the root value of the data:- ");
    scanf("%d",&data);
    init(&root,data);
    int choice;
    while(1)
    {
        printf("1.Insert\n2.Height\n3.Inorder Display\n4.Preoder Display\n5.Postorder Display\n6.Predecessor of a value\n7.Successor of a value\n8.Exit\nEnter your choice:-\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                char value;
                printf("Enter the value to be inserted:- ");
                scanf("%c",&value);
                insert(root,value);
                break;
            case 2:
                int h;
                h=height(root);
                printf("The height of the tree is:- %d\n",h);
                break;
            case 3:
                printf("The inorder display of the tree is:-\n");
                display_inorder_threaded(root);           
                break;
            case 4:
                printf("The postorder display of the tree is:-\n");
                display_preorder_threaded(root);
                printf("\n");
                break;
            case 5:
                printf("The preorder display of the tree is:-\n");
                display_postorder_threaded(root);
                printf("\n");
                break;
            case 6:
                char value2;
                printf("Enter the value whose predecessor u want to know:- ");
                scanf("%c",&value2);
                printf("The predecessor is:- %c\n",predecessor(value2,root));
                break;
            case 7:
                char value3;
                printf("Enter the value whose successor u want to know:- ");
                scanf("%c",&value3);
                printf("The successor is:- %c\n",successor(value3,root));
                break;
            case 8:
                printf("BYE BYE!!!\n");
                return(0);
            default:
                printf("The choice entered is invalid. Pls enter again...");
                break;
        }
    }
}

