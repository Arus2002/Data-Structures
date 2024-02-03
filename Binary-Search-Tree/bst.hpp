#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <initializer_list>
#include <vector>

struct TreeNode {
    TreeNode(int val)
        : val{val}
        , left{nullptr}
        , right{nullptr} {}

    int val;
    TreeNode* left;
    TreeNode* right;
};

class BST {
public:
    BST();
    BST(std::vector<int>&& vec);
    BST(const BST& rhs);
    BST& operator=(const BST& rhs);
    BST(BST&& rhs);
    BST& operator=(BST&& rhs);
    ~BST();

    void remove(int val);
    void insert(int val);
    bool find(int val) const;
    std::size_t getHeight() const;
    void inorderTraverse() const;
    void preorderTraverse() const;
    void postorderTraverse() const;

public:
    int getSuccessor(int val) const;
    int getPredeccessor(int val) const;
    int getMin() const;
    int getMax() const;

private:
    TreeNode* insert(TreeNode* root, int val);
    TreeNode* remove(TreeNode* root, int val);
    TreeNode* find(TreeNode* root, int val) const;
    void inorderTraverse(TreeNode* root) const;
    void preorderTraverse(TreeNode* root) const;
    void postorderTraverse(TreeNode* root) const;
    std::size_t getHeight(TreeNode* root) const;
    TreeNode* fromArrayToList(const std::vector<int>& vec, int left, int right);
    void clean(TreeNode* root);
    TreeNode* getMax(TreeNode* node) const;
    TreeNode* getMin(TreeNode* node) const;
    TreeNode* getSuccessor(TreeNode* node) const;

private:
    TreeNode* m_root;
    std::size_t m_size;
};

#endif