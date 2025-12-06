#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "treeNode.h"
#include "tree_iterator.h"
#include "reverse_tree_iterator.h"
#include "tree_algorithms.h"
#include <functional>
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class binaryTree
{
private:
    treeNode<T>* root;
    std::function<bool(const T&, const T&)> comparator;

public:
    using iterator = tree_iterator<T>;
    using reverse_iterator = reverse_tree_iterator<T>;

    binaryTree();
    binaryTree(std::function<bool(const T&, const T&)> comp);
    ~binaryTree();

    iterator begin();
    iterator end();

    reverse_iterator rbegin()
    {
        treeNode<T>* rightmost = root;
        if (rightmost != nullptr)
            while (rightmost->right != nullptr)
                rightmost = rightmost->right;
        return reverse_iterator(rightmost, root);
    }

    reverse_iterator rend(){ return reverse_iterator(nullptr, root); }

    void push(const T& value);
    bool remove(const T& value);
    void clear();
    bool empty() const;
    size_t size() const;

    template<typename Predicate>
    iterator find_if(Predicate pred);

    void printTree() const;
    tree_algorithms<T> get_algorithms();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const binaryTree<U>& tree);

private:
    treeNode<T>* insert(treeNode<T>* node, treeNode<T>* parent, const T& value);
    treeNode<T>* findMinNode(treeNode<T>* node) const;
    void clearRecursive(treeNode<T>* node);
    size_t sizeRecursive(treeNode<T>* node) const;

    template<typename Predicate>
    treeNode<T>* findIfRecursive(treeNode<T>* node, Predicate pred) const;

    void printRecursive(treeNode<T>* node, int depth = 0) const;
};

#include "../source/binryTree.tpp"

#endif // BINARY_TREE_H