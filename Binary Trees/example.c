NODE* splay2(NODE* root,int key)
{
    if(root==NULL || root->data == key)
        return root;
    if(key < root->data) 
    {
        if(root->left==NULL)                        //Zig cond.
            return root;

        if(key < root->left->data)                  // Zig-Zig cond.
        {
            if(root->left->data == key)
                return right_rotate(root);

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
