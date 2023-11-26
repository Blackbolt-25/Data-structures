#include<stdio.h>
#include<stdlib.h>


typedef struct node{
  char data;
  struct node* right;
  struct node* left;
  int islt;
  int isrt;
}NODE;


NODE* create(char data)
{
  NODE* newnode = (NODE*)malloc(sizeof(NODE));
  newnode->data=data;  
  newnode->right=NULL;
  newnode->left=NULL;
  newnode->islt=1;
  newnode->isrt=1;
  return newnode;
}


void init(NODE** root, char root_value)
{
  NODE* dummy = create('D');
  dummy->isrt = 0;
  dummy->islt = 0;
  (*root) = create(root_value);
  dummy->right = *root; 
  dummy->left = dummy;
  (*root)->right = dummy;
  (*root)->left = dummy;
}


void insert(NODE** root, char value)
{
  NODE* newnode = create(value);
  NODE* current = (*root);
  while(current)
  {
    if(value < current->data)
    {
      if(current->islt)
      {
        newnode->left=current->left;
        current->left=newnode;
        newnode->right=current;
        current->islt=0;
        return;
      }
      current=current->left;
    }
    if(value > current->data)
    {
      if(current->isrt)
      {
        newnode->right=current->right;
        current->right=newnode;
        newnode->left=current;
        current->isrt=0;
        return;
      }
      current=current->right;
    }
  }
}


NODE* leftmost(NODE* root)
{
  while(!root->islt)
    root=root->left;
  return root;
}

NODE* rightmost(NODE* root)
{
  while(!root->isrt)
    root=root->right;
  return root;
}

char successor(NODE* root)
{
  if(root->isrt)
  {
    NODE* ans = root->right;  
    if(ans->data == 'D')
      ans = leftmost(ans->right);
    return ans->data; 
  }
  else
  {
    NODE* ans = leftmost(root->right);
    return ans->data;
  }
  return '0';
}


char predecessor(NODE* root)
{
  if(root->islt)
  {
    NODE* ans = root->left;
    if(ans->data == 'D')
      ans = rightmost(ans->right);
    return ans->data;
  }
  else
  {
    NODE* ans = rightmost(root->left) ;
    return ans->data;
  }
  return '0';
}


void inorder_traversal(NODE* root)
{
  char temp;
  NODE* current = leftmost(root);
  while(current->data != 'D')  
  {
    temp = successor(current);
    printf("%c ",current->data);
    current=current->right;
  }
}


void preorder(NODE* root)
{
  printf("%c ",root->data);
  if(!root->islt)
    preorder(root->left);
  if(!root->isrt)
    preorder(root->right);
}

void postorder(NODE* root)
{
  if(!root->islt)
    postorder(root->left);
  if(!root->isrt)
    postorder(root->right);
  printf("%c ",root->data);
}

NODE* search(NODE* root,char value)
{
  if(root->data > value && !root->islt)
    return search(root->left,value);
  else if(root->data < value && !root->isrt)
    return search(root->right,value);
  else if(root->data == value)
      return root;
  return root;
}


int main() 
{
    NODE* root = NULL;
    char value;
    printf("Enter the value for the root of the node: ");
    scanf(" %c", &value);
    getchar();  
    init(&root, value);
    NODE* temp;
    int choice;
    while (1) 
    {
        printf("\n1. Insert\n2. Inorder Traversal\n3. Inorder Successor\n4. Inorder Predecessor\n5. Search\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf(" %c", &value);
                insert(&root, value);
                printf("The value has been inserted.\n");
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder_traversal(root);
                break;
            case 3:
                printf("Enter the value whose inorder successor you want: ");
                scanf(" %c", &value);
                temp = search(root, value);
                if (temp->data == value)
                    printf("The Inorder Successor is: %c\n", successor(temp));
                else
                    printf("The entered value does not exist.\n");
                break;
            case 4:
                printf("Enter the value whose inorder predecessor you want: ");
                scanf(" %c", &value);
                temp = search(root, value);
                if (temp->data == value)
                    printf("The Inorder Predecessor is: %c\n", predecessor(temp));
                else
                    printf("The entered value does not exist.\n");
                break;
            case 5:
                printf("Enter the value to search: ");
                scanf(" %c", &value);
                temp = search(root, value);
                if (temp->data == value)
                    printf("The entered value exists in the Threaded Binary tree.\n");
                else
                    printf("The entered value does not exist in the Threaded Binary tree.\n");
                break;
            case 6:
                printf("BYE BYE!!!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
