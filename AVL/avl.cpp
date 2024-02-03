#include "avl.hpp"

#include <cmath>

AVL::AVL()
    : m_root{nullptr}
    , m_size{0} {}

AVL::~AVL() {
    clean(m_root);
}

void AVL::clean(TreeNode* node) {
    if (node != nullptr) {
        clean(node -> left);
        clean(node -> right);
        delete node;
    }
}

int AVL::getHeight(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(getHeight(node -> left), getHeight(node -> right)) + 1;
}

int AVL::getBF(TreeNode* left, TreeNode* right) const {
    return getHeight(left) - getHeight(right);
}

int AVL::getBF(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    if (node -> left == nullptr && node -> right == nullptr) {
        return 0;
    }
    if (node -> left == nullptr) {
        return -getHeight(node -> right);
    }
    if (node -> right == nullptr) {
        return -getHeight(node -> left);
    }
    return getBF(node -> left, node -> right);
}

TreeNode* AVL::find(TreeNode* node, int val) {
    if (node == nullptr) {
        return nullptr;
    }
    if (val < node -> val) {
        find(node -> left, val);
    }
    else if (val > node -> val) {
        find(node -> right, val);
    }
    return node;
}

bool AVL::find(int val) {
    if (find(m_root, val) != nullptr) {
        return true;
    }
    return false;
}

int AVL::height() {
    return getHeight(m_root);
}

TreeNode* AVL::LLCase(TreeNode* node) {
    TreeNode* tmp = node -> left;
    node -> left = tmp -> right;
    tmp -> right = node;
    return tmp;
}

TreeNode* AVL::RRCase(TreeNode* node) {
    TreeNode* tmp = node -> right;
    node -> right = tmp -> left;
    tmp -> left = node;
    return tmp;
}

TreeNode* AVL::insert(TreeNode* node, int val) {
    if (node == nullptr) {
        return new TreeNode(val);
    }
    if (val < node -> val) {
        node -> left = insert(node -> left, val);
    }
    else {
        node -> right = insert(node -> right, val);
    }

    int bf = getBF(node);
    if (bf > 1 && val > node -> left -> val) { //inserta exel left subtree-i aj masum
        node -> left = RRCase(node -> left);
        return LLCase(node);
    }
    if (bf > 1 && val < node -> left -> val) { //inserta exel left subtree-i dzax masum
        return LLCase(node);
    }
    if (bf < -1 && val < node -> right -> val) { //inserta exel right subtree-i dzax masum
        node -> right = LLCase(node -> right);
        return RRCase(node);
    }
    if (bf < -1 && val > node -> right -> val) { //inserta exel right subtree-i aj masum
        return RRCase(node);
    }
    return node;
}

void AVL::insert(int val) {
    m_root = insert(m_root, val);
}

TreeNode* AVL::getMax(TreeNode* node) const {
    if (node != nullptr) {
        getMax(node -> right);
    }
    return node;
}

TreeNode* AVL::remove(TreeNode* node, int val) {
    if (node == nullptr) {
        return node;
    }
    if (node -> val > val) {
        node -> left = remove(node -> left, val);
    }
    else if (node -> val < val) {
        node -> right = remove(node -> right, val);
    }
    else {
        if (node -> left == nullptr) {
            TreeNode* tmp = node -> right;
            delete node;
            return tmp; //has only right child
        }
        else if (node -> right == nullptr) {
            TreeNode* tmp = node -> left;
            delete node;
            return tmp; //has only left child
        }
        else {
            TreeNode* tmp = getMax(node -> left);
            node -> val = tmp -> val;
            node -> right = remove(node -> right, tmp -> val); //has two children
        }
    }
    int bf = getBF(node);
    if (bf > 1 && getBF(node -> left) >= 0) {
        return LLCase(node);
    }
    if (bf > 1 && getBF(node -> left) < 0) {
        node -> left = RRCase(node -> left);
        return LLCase(node);
    }
    if (bf < -1 && getBF(node -> right) <= 0) {
        return RRCase(node);
    }
    if (bf < -1 && getBF(node -> right) > 0) {
        node -> right = LLCase(node -> right);
        return RRCase(node);
    }
    return node;
}

void AVL::remove(int val) {
    remove(m_root, val);
}
