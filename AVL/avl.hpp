#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val)
        : val{val}
        , left{nullptr}
        , right{nullptr} {}
};

class AVL {
public:
    AVL();
    ~AVL();
    int getHeight(TreeNode* node) const;
    int getBF(TreeNode* node) const;
    void insert(int val);
    void remove(int val);
    bool find(int val);
    int height();

private:
    TreeNode* LLCase(TreeNode* node);
    TreeNode* RRCase(TreeNode* node);
    TreeNode* insert(TreeNode* node, int val);
    TreeNode* remove(TreeNode* node, int val);
    TreeNode* find(TreeNode* node, int val);
    TreeNode* getMax(TreeNode* node) const;
    int getBF(TreeNode* left, TreeNode* right) const;
    void clean(TreeNode*);
private:
    TreeNode* m_root;
    std::size_t m_size;
};

#endif