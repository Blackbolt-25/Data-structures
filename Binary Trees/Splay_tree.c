//Splay Tree:- It is a varient of BST. The other varients of BST are AVL, Red-Black Tree .Process of a tree on which node you are going to perform operation so that particular node stay at the root.

//key point:-
//i)Splay tree is roughly BST (AVL is complete BST)
//Height does not matter.

//Operations to be performed on splay tree:-
//i)Search , Insert, Delete , Splay.

//Advantages of Splay tree
//i) Minimize the memory space. (in AVL tree every Node stores,-1 , 0 and 1)
//ii)It is faster than AVL and Red-Black tree.

//Drawbacks:-
//i)It does not always give a Balanced BST. This may lead to performance degradation in worst-case scenarios.
//ii)Applicable only for frequently use nodes. 

//Applications:-
//i)Windows NT and GCC compiler uses splay tree concept to implement.
//ii)To implement cache memory (Cookies in web browser).

//Rotations in splay tree
//i)Zig (Right rotation)
//ii)Zag (Left rotation)
//iii)Zag Zag (Left Left rotation)
//iv)Zig Zig (Right Right rotation)
//v)Zig Zag (Right Left rotation)
//vi)Zag Zig (Left Right rotation)

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}NODE;

NODE* create(int data)
{
    NODE* newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=data;
    newnode->left=newnode->right=NULL;
    return newnode;
}

NODE* left_rotate(NODE* x)
{
    NODE* y=x->right;
    NODE* T2=y->left;

    y->left=x;
    x->right=T2;
    return y;
}

NODE* right_rotate(NODE* y)
{
    NODE* x=y->left;
    NODE* T1=x->right;

    x->right=y;
    y->left=T1;
    return x;
}


NODE* splay(node* root, int key)
{
    if (root == NULL || root->key == key)
        return root;
 
    if (root->key > key) {
        if (root->left == NULL)
            return root;
        if (root->left->key > key) {                            //Zig-Zig cond.
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) {                       //Zag-Zig cond.
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else {
        if (root->right == NULL)
            return root;
        if (root->right->key > key) {                           //Zig-Zag cond.
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) {                      //Zag-Zag cond.
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root: leftRotate(root);
    }
}


NODE* splay2(NODE* root,int key)
{
    if(root==NULL)
    {
        NODE* newnode=create(key);
        return newnode;
    }

    if(key < root->data) 
    {
        if(root->left==NULL)                        //Zig cond.
        {
            root->left=splay2(root->left,key);
            root=right_rotate(root);
            return root;
        }

        if(key < root->left->data)                  // Zig-Zig cond.
        {
            if(root->left->left!=NULL)              // Cond to check the ancestor (Grandparent) node.
                root->left=splay2(root->left,key);
            else                                    // Zig-Zig cond.
            {
                root->left->left=splay2(root->left->left,key);
                root=right_rotate(root);
            }
            return (root->left==NULL) ? root : right_rotate(root);
        }
        else if(key > root->left->data)             // Zag-Zig cond. (Grandparent node checking not required over here.)
        {
            root->left=splay2(root->left,key);
            return (root->left==NULL) ? root : right_rotate(root);
        }
    }
    else if(key > root->data)
    {
        if(root->right == NULL)                     //Zag cond.
        {
            root->right=splay2(root->right,key);
            root=left_rotate(root);
            return root;
        }

        if(key > root->right->data)                 // Zag-Zag cond.
        {
            if(root->right->right != NULL)          // Cond to check the ancestor (Grandparent) node. 
                root->right=splay2(root->right,key);
            else                                    // Zag-Zag cond.
            {
                root->right->right=splay2(root->right->right,key);
                root=left_rotate(root);
            }
            return (root->right==NULL) ? root : left_rotate(root);
        }
        else if(key < root->right->data)            // Zig-Zag cond. (Grandparent node checking not required over here.)
        {
            root->right=splay2(root->right,key);
            return (root->right==NULL) ? root : left_rotate(root);
        }
    }
    return root;
}


NODE* search(NODE* root,int key)
{
    return splay(root, key);
}

NODE* delete(NODE* root, int key)
{
    if(root==NULL)
        return root;

    root=splay(root,key);
    if(root->data !=key)
        return root;

    if(root->left == NULL)
    {
        NODE* temp=root;
        root=root->right;
    }
    else
    {
        NODE* temp=root;
        root=splay(root->left,key);
        root->right=temp->right;
    }

    free(temp);
    return root;
}


NODE* insert2(NODE* root, int key)
{
    root=splay2(root,key);
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
    root=insert2(root,15);
    root=insert2(root,10);
    root=insert2(root,17);
    root=insert2(root,7);
    inorder(root);
    int temp=search(root,15);
    inorder(root);
}

