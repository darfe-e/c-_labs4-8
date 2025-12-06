#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include "treeNode.h"
#include <stdexcept>

template <typename T>
class tree_iterator
{
private:
    treeNode<T>* current;

public:

    tree_iterator();
    tree_iterator(treeNode<T>* node);
    tree_iterator(const tree_iterator& other);

    tree_iterator& operator=(const tree_iterator& other);

    T& operator*() const;
    T* operator->() const;

    tree_iterator& operator++();
    tree_iterator operator++(int);

    tree_iterator& operator--();
    tree_iterator operator--(int);

    bool operator==(const tree_iterator& other) const;
    bool operator!=(const tree_iterator& other) const;

    treeNode<T>* getNode() const;
};

#include "../source/tree_iterator.tpp"

#endif // TREE_ITERATOR_H