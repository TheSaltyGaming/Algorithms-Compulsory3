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

/**
 * \brief Does a breadth first traversal of the tree.
 * \param root The root to perform the traversal from. 
 */
void GenTree::BreadthFirstTraversal(TreeNode * root)
{
    if (isEmpty(root)) return;

    // Making a queue for traversal. 
    std::queue<TreeNode *> queue;
    queue.push(root);
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

/**
 * \brief Returns the root of the tree.
 * \return root of the tree.
 */
TreeNode* GenTree::GetRoot()
{
    //is this redundant?
    //get parent until it doesn't find a parent??
    return TreeRoot;
}

/**
 * \brief Returns the parent of a node
 * \param node node to return the parent of
 * \return parent of node
 */
TreeNode* GenTree::GetParent(TreeNode* node)
{
    if (isEmpty(node)) return nullptr;
    if (node == TreeRoot) return nullptr;

    return node->Parent;
}

/**
 * \brief Adds a new child from a node
 * \param data the data value of the child
 * \param ParentNode the node to create the child from
 */
void GenTree::AddChild(int data, TreeNode* ParentNode)
{
    TreeNode* child = new TreeNode(data, ParentNode);
    AllNodeVector.push_back(child);
}

/**
 * \brief Creates a children at a random node in the tree
 * \param data the data value of the child
 */
void GenTree::AddRandomChild(int data)
{
    srand(time(NULL));
    TreeNode* randomparent = AllNodeVector[rand() % AllNodeVector.size()];
    TreeNode* randomchild = new TreeNode(data, randomparent);
    AllNodeVector.push_back(randomchild);
}

/**
 * \brief Deletes a node from the tree and links it's children to it's parent
 * \param node node to delete
 */
void GenTree::DeleteNode(TreeNode* node)
{
    //Delete node from the children vector of the parent
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
    //Links the children of the node to the parent of the node
    //Idk if we were supposed to do this, but it made sense to me so i did it 
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

/**
 * \brief Returns the children of a node
 * \param node node to return the children of
 * \return child nodes of node
 */
std::vector<TreeNode*> GenTree::GetChildren(TreeNode* node)
{
    return node->children;
}

/**
 * \brief Returns the size(number of nodes) in the tree
 * \return number of nodes in tree
 */
int GenTree::size()
{
    return AllNodeVector.size();
}

/**
 * \brief Finds the depth of a spesific node
 * \param node node to find depth of
 * \return depth of node
 */
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

/**
 * \brief Returm the height of the tree
 * \return height of tree
 */
int GenTree::height()
{
    if (isEmpty(TreeRoot)) return 0;
    int depth = 0;
    // Making a queue for traversal. 
    std::queue<TreeNode *> queue;
    queue.push(TreeRoot);
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
        
        depth++;
    }
    //Subtracting 1 here to get the correct number, cause I forgot that the root is depth 0
    return depth-1;
}

/**
 * \brief check if node is empty
 * \param node node to check
 * \return true if node is empty
 */
bool GenTree::isEmpty(TreeNode* node)
{
    //if you wanna check if the entire tree is empty, just call this with root
    return node == nullptr;
}

/**
 * \brief Checks if node is root
 * \param node node to check
 * \return true if the node is the root
 */
bool GenTree::isRoot(TreeNode* node)
{
    return (node != nullptr) && (GetParent(node) == nullptr);
}

/**
 * \brief Checks if a node is a leaf node
 * \param node node to check
 * \return true if leaf node
 */
bool GenTree::isLeaf(TreeNode* node)
{
    return (node != nullptr) && (GetChildren(node).empty());
}