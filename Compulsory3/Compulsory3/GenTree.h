#pragma once
#include <vector>

class TreeNode;

class GenTree
{
public:
    GenTree();

    TreeNode* GetRoot();
    TreeNode* GetParent(TreeNode* node);
    void AddChild(int data, TreeNode* ParentNode);
    void AddRandomChild(int data);
    void DeleteNode(TreeNode* node);
    std::vector<TreeNode*> GetChildren(TreeNode* node);
    std::vector<TreeNode*> AllNodeVector;

    int size();
    int depth(TreeNode* node);
    int height();
    bool isEmpty(TreeNode* node);
    bool isRoot(TreeNode* node);
    bool isLeaf(TreeNode* node);

    void BreadthFirstTraversal(TreeNode * root);
private:
    TreeNode* TreeRoot;
    
};
