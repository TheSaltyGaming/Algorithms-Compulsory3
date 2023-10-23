#pragma once
#include <vector>

class TreeNode
{
public:
    int data;
    std::vector<TreeNode*> children;
    TreeNode(int value) : data(value){}
    TreeNode(int value, TreeNode* ParentNode) : data(value), Parent(ParentNode)
    {
        if (Parent != nullptr)
        {
            Parent->children.push_back(this);
        }
    }
    TreeNode* Parent = nullptr;
};