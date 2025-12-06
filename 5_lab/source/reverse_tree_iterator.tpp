#ifndef REVERSE_TREE_ITERATOR_TPP
#define REVERSE_TREE_ITERATOR_TPP

#include "../headers/reverse_tree_iterator.h"

template <typename T>
reverse_tree_iterator<T>::reverse_tree_iterator()
        : current(nullptr), tree_root(nullptr) {}

template <typename T>
reverse_tree_iterator<T>::reverse_tree_iterator(treeNode<T>* node, treeNode<T>* root)
        : current(node), tree_root(root) {}

template <typename T>
reverse_tree_iterator<T>::reverse_tree_iterator(const reverse_tree_iterator& other)
        : current(other.current), tree_root(other.tree_root) {}

template <typename T>
reverse_tree_iterator<T>& reverse_tree_iterator<T>::operator=(const reverse_tree_iterator& other)
{
    if (this != &other)
    {
        current = other.current;
        tree_root = other.tree_root;
    }
    return *this;
}

template <typename T>
T& reverse_tree_iterator<T>::operator*() const
{
    if (current == nullptr)
        throw std::runtime_error("Dereferencing null iterator");
    return current->data;
}

template <typename T>
T* reverse_tree_iterator<T>::operator->() const
{
    if (current == nullptr)
        throw std::runtime_error("Dereferencing null iterator");
    return &(current->data);
}

template <typename T>
reverse_tree_iterator<T>& reverse_tree_iterator<T>::operator++()
{
    // ++ для reverse идет к предыдущему (меньшему) элементу
    if (current == nullptr)
    {
        // Для rend() нужно найти минимальный элемент
        if (tree_root == nullptr)
            return *this;

        // Идем к минимальному элементу
        current = tree_root;
        while (current->left != nullptr)
            current = current->left;
        return *this;
    }

    // Логика как у обычного итератора для --
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
reverse_tree_iterator<T> reverse_tree_iterator<T>::operator++(int)
{
    reverse_tree_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
reverse_tree_iterator<T>& reverse_tree_iterator<T>::operator--()
{
    // -- для reverse идет к следующему (большему) элементу
    if (current == nullptr)
    {
        // Для rbegin() нужно найти максимальный элемент
        if (tree_root == nullptr)
            return *this;

        // Идем к максимальному элементу
        current = tree_root;
        while (current->right != nullptr)
            current = current->right;
        return *this;
    }

    // Логика как у обычного итератора для ++
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
reverse_tree_iterator<T> reverse_tree_iterator<T>::operator--(int)
{
    reverse_tree_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool reverse_tree_iterator<T>::operator==(const reverse_tree_iterator& other) const
{
    return current == other.current;
}

template <typename T>
bool reverse_tree_iterator<T>::operator!=(const reverse_tree_iterator& other) const
{
    return !(*this == other);
}

template <typename T>
treeNode<T>* reverse_tree_iterator<T>::getNode() const
{
    return current;
}

#endif // REVERSE_TREE_ITERATOR_TPP