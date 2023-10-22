#pragma once
#include <vector>

class TreeNode
{
public:
    int data;
    std::vector<TreeNode*> children;
    TreeNode(int value) : data(value){}
};