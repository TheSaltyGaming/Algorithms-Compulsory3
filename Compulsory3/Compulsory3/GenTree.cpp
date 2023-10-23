#include "GenTree.h"

#include <iostream>
#include <queue>

#include "TreeNode.h"

using namespace std;

GenTree::GenTree()
{
    TreeNode* root = new TreeNode(8);
    TreeRoot = root;
    AllNodeVector.push_back(root);

    TreeNode* child10 = new TreeNode(2, root);
    TreeNode* child11 = new TreeNode(4, root);
    TreeNode* child12 = new TreeNode(16, root);
    TreeNode* child13 = new TreeNode(24, root);
    AllNodeVector.push_back(child10);
    AllNodeVector.push_back(child11);
    AllNodeVector.push_back(child12);
    AllNodeVector.push_back(child13);


    TreeNode* child20 = new TreeNode(1, child10);
    TreeNode* child21 = new TreeNode(1, child10);
    AllNodeVector.push_back(child20);
    AllNodeVector.push_back(child21);
    


    TreeNode* child30 = new TreeNode(32, child12);
    TreeNode* child31 = new TreeNode(48, child12);
    AllNodeVector.push_back(child30);
    AllNodeVector.push_back(child31);


    TreeNode* child40 = new TreeNode(56, child13);
    TreeNode* child41 = new TreeNode(640, child13);
    AllNodeVector.push_back(child40);
    AllNodeVector.push_back(child41);

    AddRandomChild(42069);
    AddChild(112, child11);
    //DeleteNode(child12);


    
    BreadthFirstTraversal(root);

    std::cout << endl;
    std::cout << "Root: " << root->data << endl;
    std::cout << "Parent of " << child30->data << " is: " << GetParent(child30)->data << endl;
    std::cout << "Size of the tree is : " << size() << endl;
    std::cout << "Height of the tree is : " << height() << endl;
    std::cout << "Depth of 56 is : " << depth(child40) << endl;
    
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
        int nodes = queue.size();
 
        // If this node has children
        while (nodes > 0)
        {
            // Dequeue an item from queue and print it
            TreeNode * temp = queue.front();
            queue.pop();
            std::cout << temp->data << " ";
  
            // Enqueue all children of the dequeued item
            for (int i=0; i<temp->children.size(); i++)
                queue.push(temp->children[i]);
            nodes--;
        }
        
  
        std::cout << endl; // Print new line between two levels
    }
}

TreeNode* GenTree::GetRoot()
{
    //is this redundant?
    //get parent until it doesn't find a parent??
    return TreeRoot;
}

TreeNode* GenTree::GetParent(TreeNode* node)
{
    if (isEmpty(node)) return nullptr;
    if (node == TreeRoot) return nullptr;

    return node->Parent;
}

void GenTree::AddChild(int data, TreeNode* ParentNode)
{
    TreeNode* child = new TreeNode(data, ParentNode);
    AllNodeVector.push_back(child);
}

void GenTree::AddRandomChild(int data)
{
    srand(time(NULL));
    TreeNode* randomparent = AllNodeVector[rand() % AllNodeVector.size()];
    TreeNode* randomchild = new TreeNode(data, randomparent);
    AllNodeVector.push_back(randomchild);
}

void GenTree::DeleteNode(TreeNode* node)
{
    TreeNode* parent = GetParent(node);
    if (parent != nullptr)
    {
        for (int i = 0; i < parent->children.size(); i++)
        {
            if (parent->children[i] == node)
            {
                parent->children.erase(parent->children.begin() + i);
                break;
            }
        }
    }
    //Delete node from AllNodeVector
    for (int i = 0; i < AllNodeVector.size(); i++)
    {
        if (AllNodeVector[i] == node)
        {
            AllNodeVector.erase(AllNodeVector.begin() + i);
            break;
        }
    }
    if (!isLeaf(node))
    {
        for (TreeNode* child : node->children)
        {
            child->Parent = parent;
            parent->children.push_back(child);
        }
    }
    delete node;
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

    // Traversal queue 
    std::queue<TreeNode *> queue;
    queue.push(TreeRoot);
    while (!queue.empty())
    {
        int nodes = queue.size();
 
        // If this node has children
        while (nodes > 0)
        {
            // Dequeue an item from queue and print it
            TreeNode * temp = queue.front();
            queue.pop();
            depth++;
  
            // Enqueue all children of the dequeued item
            for (int i=0; i<temp->children.size(); i++)
                queue.push(temp->children[i]);
            nodes--;
        }
  
        std::cout << endl; // Print new line between two levels
    }
    return depth-1;
}

//TODO: Fix this node right here please
int GenTree::depth(TreeNode* node)
{
    if (isEmpty(node)) return 0;
    if (isRoot(node)) return 0;
    int depth = 0;
    while (GetParent(node) != nullptr)
    {
        node = GetParent(node);
        depth++;
    }
    return depth;
}

int GenTree::height()
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

        //Add more to depth
        depth++;
    }
    //Subtracting 1 here to get the correct number, cause I forgot that the root is depth 0
    return depth-1;
}

bool GenTree::isEmpty(TreeNode* node)
{
    //if you wanna check if the entire tree is empty, just call this with root
    return node == nullptr;
}

bool GenTree::isRoot(TreeNode* node)
{
    return (node != nullptr) && (GetParent(node) == nullptr);
}

bool GenTree::isLeaf(TreeNode* node)
{
    return (node != nullptr) && (GetChildren(node).empty());
}