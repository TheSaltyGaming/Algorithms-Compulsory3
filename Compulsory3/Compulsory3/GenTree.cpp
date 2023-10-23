#include "GenTree.h"

#include <iostream>
#include <queue>

#include "TreeNode.h"

using namespace std;

GenTree::GenTree()
{
    TreeNode *root = newNode(8);
    TreeRoot = root;

    //There has to be an easier way to do this.
    //TODO: Make this look cleaner you dumbo
    (root->children).push_back(newNode(2));
    (root->children).push_back(newNode(4));
    (root->children).push_back(newNode(16));
    (root->children).push_back(newNode(24));
    (root->children[0]->children).push_back(newNode(1));
    (root->children[0]->children).push_back(newNode(1));
    (root->children[2]->children).push_back(newNode(32));
    (root->children[2]->children).push_back(newNode(48));
    (root->children[3]->children).push_back(newNode(56));
    (root->children[3]->children).push_back(newNode(640));
    (root->children[3]->children[0]->children).push_back(newNode(640));

    
    BreadthFirstTraversal(root);

    std::cout << endl;
    std::cout << "Root: " << root->data << endl;
std::cout << root->children[3]->children[0]->data << endl;
    std::cout << "Parent of 56 is: " << GetParent(root->children[3]->children[0])->data << endl;
    std::cout << "Size of the tree is : " << size() << endl;
    std::cout << "Depth of the tree is : " << depth() << endl;
    
}

//temp code now
void GenTree::BreadthFirstTraversal(TreeNode * root)
{
    if (isEmpty(root)) return;

    // Making a queue for traversal. 
    std::queue<TreeNode *> queue;  // Create a queue
    queue.push(root); // Enqueue root 
    while (!queue.empty())
    {
        int n = queue.size();
 
        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            TreeNode * p = queue.front();
            queue.pop();
            std::cout << p->data << " ";
  
            // Enqueue all children of the dequeued item
            for (int i=0; i<p->children.size(); i++)
                queue.push(p->children[i]);
            n--;
        }
        
  
        std::cout << endl; // Print new line between two levels
    }
}

TreeNode* GenTree::GetRoot()
{
    //is this redundant?
    return TreeRoot;
}

TreeNode* GenTree::GetParent(TreeNode* node)
{
    if (isEmpty(node)) return nullptr;

    if (node == TreeRoot) return nullptr;

    std::queue<TreeNode*> queue;
    queue.push(TreeRoot);
    
    while (!queue.empty()) {
        int n = queue.size();
        
        TreeNode* parent = nullptr;
        
        while (n > 0) {
            TreeNode* current = queue.front();
            queue.pop();

            for (TreeNode* child : current->children) {
                if (child == node) {
                    return parent;
                }
                
                queue.push(child);
            }
            
            parent = current;
            n--;
        }
    }
    
    return nullptr;
}

TreeNode* GenTree::newNode(int value)
{
    TreeNode* newNode = new TreeNode(value); // Create a new TreeNode with the provided value
    return newNode;
}

std::vector<TreeNode*> GenTree::GetChildren(TreeNode* node)
{
    return node->children;
}

int GenTree::size()
{
    //I know this is just the traversal code, but it works tho right?
    int depth = 0;
    if (isEmpty(TreeRoot)) return 0;

    // Making a queue for traversal. 
    std::queue<TreeNode *> queue;  // Create a queue
    queue.push(TreeRoot); // Enqueue root 
    while (!queue.empty())
    {
        int n = queue.size();
 
        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            TreeNode * p = queue.front();
            queue.pop();
            depth++;
  
            // Enqueue all children of the dequeued item
            for (int i=0; i<p->children.size(); i++)
                queue.push(p->children[i]);
            n--;
        }
  
        std::cout << endl; // Print new line between two levels
    }
    return depth;
}

//TODO: Fix this node right here please
int GenTree::depth(TreeNode* node)
{
    if (isEmpty(TreeRoot)) return 0;
    int depth = 0;
    // Making a queue for traversal. 
    std::queue<TreeNode *> queue;  // Create a queue
    queue.push(TreeRoot); // Enqueue root 
    while (!queue.empty())
    {
        int levelSize = queue.size();

        for (int i = 0; i < levelSize; i++)
        {
            TreeNode *node = queue.front();
            queue.pop();

            for (TreeNode *child : node->children)
                queue.push(child);
        }

        // Increment the depth after processing each level
        depth++;
    }
    return depth;
}

bool GenTree::isEmpty(TreeNode* node)
{
    return false;
}

bool GenTree::isRoot(TreeNode* node)
{
    return false;
}

bool GenTree::isLeaf(TreeNode* node)
{
    return (node != nullptr) && (GetChildren(node).empty());
}