#pragma once
#include <vector>

class TreeNode;

class GenTree
{
public:
    GenTree();

    TreeNode* GetRoot();
    TreeNode* GetParent(TreeNode* node);
    TreeNode* newNode(int value);
    std::vector<TreeNode*> GetChildren(TreeNode* node);

    int size();
    int depth(TreeNode* node);
    bool isEmpty(TreeNode* node);
    bool isRoot(TreeNode* node);
    bool isLeaf(TreeNode* node);

    void BreadthFirstTraversal(TreeNode * root);
private:
    TreeNode* TreeRoot;
    
};
