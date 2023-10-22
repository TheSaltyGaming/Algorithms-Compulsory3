#include "GenTree.h"

TreeNode* GenTree::GetRoot()
{
}

TreeNode* GenTree::GetParent(TreeNode* node)
{
}

std::vector<TreeNode*> GenTree::GetChildren(TreeNode* node)
{
}

int GenTree::size()
{
}

int GenTree::depth()
{
}

bool GenTree::isEmpty(TreeNode* node)
{
    
}

bool GenTree::isRoot(TreeNode* node)
{
}

bool GenTree::isLeaf(TreeNode* node)
{
    return (node != nullptr) && (GetChildren(node).empty());
}