#include <stdio.h>
#include <stdlib.h>

// Define the threaded binary search tree (TBST) node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int is_threaded; // 1 if right pointer is threaded, 0 otherwise
}Node;
// Function to create a new TBST node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->is_threaded = 0; // Initialize as not threaded
    return newNode;
}

// Function to insert a new element into the TBST while maintaining threading
struct Node* insertInTBST(struct Node* root, int data) {
    Node* newnode=createNode(data); 
    Node* current=root;
    Node* prev=NULL;
    while(current!=NULL)
    {
        prev=current;
        if(data<current->data)
        {
            if(current->left==NULL)
            {
                newnode->right=current;
                current->left=newnode;
                newnode->is_threaded=1;
                return root;
            }
            else
                current=current->left;
        }
        else
        {
            if(!current->is_threaded)
                current=current->right;
            else
            {
                newnode->right=current->right;
                current->right=newnode;
                newnode->is_threaded=1;
                current->is_threaded=0;
                return root;
            }
        }
    }
    return root;
}

struct Node* createroot(Node* root,int data)
{
        Node* dummy=createNode(-1);
        root=createNode(data);
        root->left=NULL;
        root->right=dummy;
        dummy->left=root;
        dummy->right=dummy;
        root->is_threaded=1;
        return root;
}

// Function to construct a TBST from an array of elements
struct Node* constructTBST(int arr[], int n) {
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        if(i==0)
            root=createroot(root,arr[i]);
        else
            root = insertInTBST(root, arr[i]);
    }
    return root;
}


// Function to add all the elements in the range to the ans array and return the total number of such elements

int rangeQueryInTBST(struct Node* root, int L, int R, int* ans) {
    Node* temp=root;
    int count=0;
    while(temp->left!=NULL)
        temp=temp->left;
    while(temp->data!=-1)
    {
        if(temp->is_threaded)
        {
            if(temp->data>=L && temp->data<=R)
                ans[count++]=temp->data;
            temp=temp->right;
        }
        else
        {
            if(temp->data>=L && temp->data<=R)
                ans[count++]=temp->data;
            temp=temp->right;
            while(temp->left!=NULL)
                temp=temp->left;
        }
    }
    return count;
}





void display(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main() {
    // Driver's Code
    

    
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int L;int R;
    scanf("%d",&L);
    scanf("%d",&R);
    struct Node* root = constructTBST(arr, n);
    
    
   int* ans= malloc(sizeof(int)*n);

    
    int i=rangeQueryInTBST(root, L, R,ans);
    display(ans,i);
    printf("\n");

    return 0;
}
