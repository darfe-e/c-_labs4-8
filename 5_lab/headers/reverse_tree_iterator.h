#ifndef REVERSE_TREE_ITERATOR_H
#define REVERSE_TREE_ITERATOR_H

#include "treeNode.h"
#include <stdexcept>

template <typename T>
class reverse_tree_iterator
{
private:
    treeNode<T>* current;
    treeNode<T>* tree_root;

public:

    reverse_tree_iterator();
    reverse_tree_iterator(treeNode<T>* node, treeNode<T>* root = nullptr);
    reverse_tree_iterator(const reverse_tree_iterator& other);

    reverse_tree_iterator& operator=(const reverse_tree_iterator& other);

    T& operator*() const;
    T* operator->() const;

    // В reverse итераторе ++ идет к меньшему, -- к большему
    reverse_tree_iterator& operator++();
    reverse_tree_iterator operator++(int);

    reverse_tree_iterator& operator--();
    reverse_tree_iterator operator--(int);

    bool operator==(const reverse_tree_iterator& other) const;
    bool operator!=(const reverse_tree_iterator& other) const;

    treeNode<T>* getNode() const;
};

#include "../source/reverse_tree_iterator.tpp"

#endif // REVERSE_TREE_ITERATOR_H