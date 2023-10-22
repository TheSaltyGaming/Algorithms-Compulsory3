#pragma once
#include <vector>

class TreeNode;

class GenTree
{
public:
    GenTree();

    TreeNode* GetRoot();
    TreeNode* GetParent(TreeNode* node);
    std::vector<TreeNode*> GetChildren(TreeNode* node);

    int size();
    int depth();
    bool isEmpty(TreeNode* node);
    bool isRoot(TreeNode* node);
    bool isLeaf(TreeNode* node);
private:
    TreeNode* root;
    
};
