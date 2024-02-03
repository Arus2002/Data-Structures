#include "bst.hpp"

#include <algorithm>
#include <stdexcept>

BST::BST()
    : m_size{0}
    , m_root{nullptr} 
{
    std::cout << "BST was created by default ctor!" << std::endl;
}

BST::BST(std::vector<int>&& vec) 
    : m_size{vec.size()}
{
    std::sort(vec.begin(), vec.end());
    m_root = fromArrayToList(vec, 0, vec.size() - 1);
}

BST::~BST() {
    clean(m_root);
}

TreeNode* BST::fromArrayToList(const std::vector<int>& vec, int left, int right) {
    if (left > right) {
        return NULL;
    }

    std::size_t mid = left + (right - left) / 2;
    TreeNode* newNode = new TreeNode(vec[mid]);

    newNode -> right = fromArrayToList(vec, mid + 1, right);
    newNode -> left = fromArrayToList(vec, left, mid - 1);

    return newNode;
}

TreeNode* BST::insert(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (root -> val >= val) {
        root -> left = insert(root -> left, val);
    }
    else {
        root -> right = insert(root -> right, val);
    }
    return root;
}

void BST::insert(int val) {
    m_root = insert(m_root, val);
    ++m_size;
}

TreeNode* BST::remove(TreeNode* node, int val) {
    if (node == nullptr) {
            return nullptr;
        }
        if (node -> val > val) {
            node -> left = remove(node -> left, val);
        }
        else if (node -> val < val) {
            node -> right = remove(node -> right, val);
        }
        else {
            if (node -> left == nullptr && node -> right == nullptr) {
                delete node;
                return nullptr;
            }
            else if(!node->left || !node->right){
                TreeNode* temp=node->left?node->left:node->right;
                delete node;
                return temp;
            }
            else {
                TreeNode* tmp = node;
                tmp = tmp -> left;
                while (tmp -> right) {
                    tmp = tmp -> right;
                }
                node -> val = tmp -> val;
                node -> left = remove(node -> left, tmp -> val); //has two children
            }
        }
        return node;
}

void BST::remove(int val) {
    remove(m_root, val);
}

TreeNode* BST::getMax(TreeNode* node) const {
    if (node != nullptr) {
        getMax(node -> right);
    }
    return node;
}

TreeNode* BST::getMin(TreeNode* node) const {
    if (node != nullptr) {
        getMin(node -> left);
    }
    return node;
}

int BST::getMin() const {
    return getMin(m_root) -> val;
}

int BST::getMax() const {
    return getMax(m_root) -> val;
}

int BST::getSuccessor(int val) const {
    if (find(m_root, val) == nullptr) {
        throw std::logic_error("~");
    } 
    TreeNode* tmp = find(m_root, val);
    if (tmp == getMax(m_root)) {
        return tmp -> val;
    }
    if (tmp -> right != nullptr) {
        return getMin(tmp -> right) -> val;
    }
    TreeNode* successor = nullptr;
    TreeNode* ancestor = m_root;
    while (ancestor != tmp) {
        if (ancestor -> val > tmp -> val) {
            successor = ancestor;
            ancestor = ancestor -> left;
        }
        else {
            ancestor = ancestor -> right;
        }
    }
    return successor -> val;
}

int BST::getPredeccessor(int val) const {
    if (find(m_root, val) == nullptr) {
        throw std::logic_error("~");
    }

    TreeNode* tmp = find(m_root, val);
    if (tmp == getMin(m_root)) {
        return tmp -> val;
    }

    if (tmp -> left != nullptr) {
        return getMax(tmp -> left) -> val;
    }

    TreeNode* predeccessor = nullptr;
    TreeNode* ancestor = m_root;
    while (ancestor != tmp) {
        if (ancestor -> val < tmp -> val) {
            predeccessor = ancestor;
            ancestor = ancestor -> right;
        }
        else {
            ancestor = ancestor -> left;
        }
    }
    return predeccessor -> val;
}

TreeNode* BST::find(TreeNode* root, int val) const {
    if (!root) {
        return nullptr;
    }
    if (val == root -> val) {
        return root;
    }
    if (val < root -> val) {
        find(root -> left, val);
    }
    else {
        find(root -> right, val);
    }
}

bool BST::find(int val) const {
    return find(m_root, val);
}

std::size_t BST::getHeight(TreeNode* root) const {
    if (!root) {
        return -1;
    }
    return std::max(getHeight((root -> left)), getHeight(root -> right)) + 1;
}

std::size_t BST::getHeight() const {
    getHeight(m_root);
}

void BST::inorderTraverse(TreeNode* root) const {
    if (root != nullptr) {
        inorderTraverse(root -> left);
        std::cout << root -> val << " ";
        inorderTraverse(root -> right);
    }
}

void BST::inorderTraverse() const {
    std::cout << "[ ";
    inorderTraverse(m_root);
    std::cout << "]" << std::endl;
}

void BST::preorderTraverse(TreeNode* root) const {
    if (root == nullptr) {
        return;
    }

    std::cout << root -> val << " ";
    preorderTraverse(root -> left);
    preorderTraverse(root -> right);
}

void BST::preorderTraverse() const {
    std::cout << "[ ";
    preorderTraverse(m_root);
    std::cout << "]" << std::endl;
}

void BST::postorderTraverse(TreeNode* root) const {
    if (root == nullptr) {
        return;
    }

    postorderTraverse(root -> left);
    postorderTraverse(root -> right);
    std::cout << root -> val << " ";
}

void BST::postorderTraverse() const {
    std::cout << "[ ";
    postorderTraverse(m_root);
    std::cout << "]" << std::endl;
}

void BST::clean(TreeNode* root) {
    if (root) {
        clean(root->left);
        clean(root->right);
        delete root;
    }
}
