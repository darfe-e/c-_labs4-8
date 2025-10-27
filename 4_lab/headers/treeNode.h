#ifndef INC_4_LAB_TREENODE_H
#define INC_4_LAB_TREENODE_H

template<typename T>
class binaryTree;

template <typename T>
class treeNode
{
    friend class binaryTree<T>;

private:
    T data;
    treeNode* left;
    treeNode* right;

public:
    treeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

#endif //INC_4_LAB_TREENODE_H