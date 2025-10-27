#ifndef INC_4_LAB_BINRYTREE_H
#define INC_4_LAB_BINRYTREE_H

#include "treeNode.h"
#include <iostream>

template <typename T>
class binaryTree
{
private:
    treeNode<T>* root;
public:
    binaryTree() : root(nullptr){}

    void push(T value);
    treeNode<T>* remove(T value);
    void printTree();
    treeNode<T>* find(const T& value);

    //template<typename returnType>
    //treeNode<T>* search(returnType (T::*getter)(), T value);

    template<typename Predicate>
    treeNode<T>* find_if(Predicate pred);

private:
    void insert(treeNode<T>* node, treeNode<T>* newNode);
    treeNode<T>* removeRecursive(treeNode<T>* node, T value);
    treeNode<T>* findMin(treeNode<T>* node);
    void printRecursive(treeNode<T>* node);

    treeNode<T>* findRecursive(treeNode<T>* node, const T& value);
   // template<typename returnType>
//    treeNode<T>* findByMethod(treeNode<T>* node, returnType (T::*getter)(), T value);
//    template<typename Predicate>
//    treeNode<T>* findIfRecursive(treeNode<T>* node, Predicate pred);
};

// === РЕАЛИЗАЦИЯ ===

template <typename T>
treeNode<T>* binaryTree<T>::find(const T& value)
{
    return findRecursive(root, value);
}

template <typename T>
treeNode<T>* binaryTree<T>::findRecursive(treeNode<T>* node, const T& value)
{
    if (!node) return nullptr;
    if (node->data == value) return node;

    treeNode<T>* left = findRecursive(node->left, value);
    if (left) return left;
    return findRecursive(node->right, value);
}

template <typename T>
void binaryTree<T>::insert(treeNode<T>* node, treeNode<T>* newNode)
{
    if (newNode->data < node->data)
    {
        if (node->left != nullptr) insert(node->left, newNode);
        else node->left = newNode;
    }
    else if (newNode->data > node->data)
    {
        if (node->right != nullptr) insert(node->right, newNode);
        else node->right = newNode;
    }
    else {
        delete newNode; // Дубликат - удаляем созданный узел
    }
}

template <typename T>
void binaryTree<T>::push(T value)
{
    treeNode<T>* newNode = new treeNode<T>(value); // Используем конструктор

    if (root == nullptr) {
        root = newNode;
    } else {
        insert(root, newNode);
    }
}

template <typename T>
treeNode<T>* binaryTree<T>::remove(T value)
{
    root = removeRecursive(root, value);
    return root;
}

template <typename T>
treeNode<T>* binaryTree<T>::removeRecursive(treeNode<T>* node, T value)
{
    if (node == nullptr) return nullptr;

    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    }
    else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    }
    else {
        if (node->left == nullptr) {
            treeNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            treeNode<T>* temp = node->left;
            delete node;
            return temp;
        }

        treeNode<T>* successor = findMin(node->right);
        node->data = successor->data;
        node->right = removeRecursive(node->right, successor->data);
    }
    return node;
}

template <typename T>
treeNode<T>* binaryTree<T>::findMin(treeNode<T>* node)
{
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
void binaryTree<T>::printTree()
{
    std::cout << "Содержимое дерева (pre-order): ";
    printRecursive(root);
    std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::printRecursive(treeNode<T>* node)
{
    if (node == nullptr) return;

    std::cout << node->data << " ";      // Текущий узел
    printRecursive(node->left);          // Левый потомок
    printRecursive(node->right);         // Правый потомок
}
//
//template <typename T>
//template <typename returnType>
//treeNode<T>* binaryTree<T>::findByMethod(treeNode<T>* node, returnType (T::*getter)(), T value)
//{
//    if (!node) return nullptr;
//
//    if ((node->data.*getter)() == value) return node;
//
//    treeNode<T>* leftResult = findByMethod(node->left, getter, value);
//    if (leftResult) return leftResult;
//
//    return findByMethod(node->right, getter, value);
//}

//template <typename T>
//template <typename returnType>
//treeNode<T>* binaryTree<T>::search(returnType (T::*getter)(), T value)
//{
//    return findByMethod(root, getter, value);
//}

//template <typename T>
//template <typename Predicate>
//treeNode<T>* binaryTree<T>::findIfRecursive(treeNode<T>* node, Predicate pred)
//{
//    if (!node) return nullptr;
//    if (pred(node->data)) return node;
//
//    treeNode<T>* leftResult = findIfRecursive(node->left, pred);
//    if (leftResult) return leftResult;
//
//    return findIfRecursive(node->right, pred);
//}

template <typename T>
template <typename Predicate>
treeNode<T>* binaryTree<T>::find_if(Predicate pred)
{
    return findIfRecursive(root, pred);
}

#endif //INC_4_LAB_BINRYTREE_H