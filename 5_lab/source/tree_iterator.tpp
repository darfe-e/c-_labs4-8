#ifndef TREE_ITERATOR_TPP
#define TREE_ITERATOR_TPP

#include "../headers/tree_iterator.h"
#include <iostream>

template <typename T>
tree_iterator<T>::tree_iterator() : current(nullptr) {}

template <typename T>
tree_iterator<T>::tree_iterator(treeNode<T>* node) : current(node) {}  // <-- ТОЛЬКО 1 ПАРАМЕТР!

template <typename T>
tree_iterator<T>::tree_iterator(const tree_iterator& other) : current(other.current) {}

template <typename T>
tree_iterator<T>& tree_iterator<T>::operator=(const tree_iterator& other)
{
    if (this != &other)
    {
        current = other.current;
    }
    return *this;
}

template <typename T>
T& tree_iterator<T>::operator*() const
{
    if (current == nullptr)
        throw std::runtime_error("Dereferencing null iterator");
    return current->data;
}

template <typename T>
T* tree_iterator<T>::operator->() const
{
    if (current == nullptr)
        throw std::runtime_error("Dereferencing null iterator");
    return &(current->data);
}

template <typename T>
tree_iterator<T>& tree_iterator<T>::operator++()
{
    if (current == nullptr)
        throw std::runtime_error("Cannot increment end iterator");

    if (current->right != nullptr)
    {
        current = current->right;
        while (current->left != nullptr)
            current = current->left;
    }
    else
    {
        treeNode<T>* parent = current->parent;
        while (parent != nullptr && current == parent->right)
        {
            current = parent;
            parent = parent->parent;
        }
        current = parent;
    }
    return *this;
}

template <typename T>
tree_iterator<T> tree_iterator<T>::operator++(int)
{
    tree_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
tree_iterator<T>& tree_iterator<T>::operator--()
{
    // Для end() итератора - бросаем исключение
    // Обычный итератор не должен поддерживать -- от end()
    if (current == nullptr)
        throw std::runtime_error("Cannot decrement end iterator");

    if (current->left != nullptr)
    {
        current = current->left;
        while (current->right != nullptr)
            current = current->right;
    }
    else
    {
        treeNode<T>* parent = current->parent;
        while (parent != nullptr && current == parent->left)
        {
            current = parent;
            parent = parent->parent;
        }
        current = parent;
    }
    return *this;
}

template <typename T>
tree_iterator<T> tree_iterator<T>::operator--(int)
{
    tree_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool tree_iterator<T>::operator==(const tree_iterator& other) const
{
    return current == other.current;
}

template <typename T>
bool tree_iterator<T>::operator!=(const tree_iterator& other) const
{
    return !(*this == other);
}

template <typename T>
treeNode<T>* tree_iterator<T>::getNode() const
{
    return current;
}

#endif // TREE_ITERATOR_TPP