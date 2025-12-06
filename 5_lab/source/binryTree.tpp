#ifndef BINARY_TREE_TPP
#define BINARY_TREE_TPP

#include "../headers/binryTree.h"

template <typename T>
binaryTree<T>::binaryTree() : root(nullptr),
                              comparator([](const T& a, const T& b) { return a < b; }) {}

template <typename T>
binaryTree<T>::binaryTree(std::function<bool(const T&, const T&)> comp)
        : root(nullptr), comparator(comp) {}

template <typename T>
binaryTree<T>::~binaryTree()
{
    clear();
}

template <typename T>
typename binaryTree<T>::iterator binaryTree<T>::begin()
{
    treeNode<T>* leftmost = root;
    if (leftmost != nullptr)
    {
        while (leftmost->left != nullptr)
            leftmost = leftmost->left;
    }
    return iterator(leftmost);  // <-- ТОЛЬКО 1 АРГУМЕНТ!
}

template <typename T>
typename binaryTree<T>::iterator binaryTree<T>::end()
{
    return iterator(nullptr);  // <-- ТОЛЬКО 1 АРГУМЕНТ!
}

template <typename T>
void binaryTree<T>::push(const T& value)
{
    if (root == nullptr)
    {
        root = new treeNode<T>(value);
    }
    else
    {
        root = insert(root, nullptr, value);
    }
}

template <typename T>
treeNode<T>* binaryTree<T>::insert(treeNode<T>* node, treeNode<T>* parent, const T& value)
{
    if (node == nullptr)
    {
        treeNode<T>* newNode = new treeNode<T>(value);
        newNode->parent = parent;
        return newNode;
    }

    if (comparator(value, node->data))
    {
        node->left = insert(node->left, node, value);
    }
    else if (comparator(node->data, value))
    {
        node->right = insert(node->right, node, value);
    }

    return node;
}

template <typename T>
bool binaryTree<T>::remove(const T& value)
{
    // Упрощенное удаление - ищем через find_if
    auto it = find_if([&value](const T& item) {
        // Здесь нужно правильно сравнивать элементы
        // Временно используем компаратор
        return !(item < value) && !(value < item);
    });

    if (it == end()) return false;

    treeNode<T>* node = it.getNode();
    if (node == nullptr) return false;

    // Реализация удаления остается прежней
    if (node->left == nullptr && node->right == nullptr)
    {
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
        }
        else
        {
            root = nullptr;
        }
        delete node;
    }
    else if (node->left == nullptr || node->right == nullptr)
    {
        treeNode<T>* child = (node->left != nullptr) ? node->left : node->right;
        child->parent = node->parent;

        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
        }
        else
        {
            root = child;
        }
        delete node;
    }
    else
    {
        treeNode<T>* successor = findMinNode(node->right);
        node->data = successor->data;

        if (successor->parent->left == successor)
            successor->parent->left = successor->right;
        else
            successor->parent->right = successor->right;

        if (successor->right != nullptr)
            successor->right->parent = successor->parent;

        delete successor;
    }

    return true;
}

template <typename T>
treeNode<T>* binaryTree<T>::findMinNode(treeNode<T>* node) const
{
    while (node != nullptr && node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
void binaryTree<T>::clear()
{
    clearRecursive(root);
    root = nullptr;
}

template <typename T>
void binaryTree<T>::clearRecursive(treeNode<T>* node)
{
    if (node == nullptr) return;

    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

template <typename T>
bool binaryTree<T>::empty() const
{
    return root == nullptr;
}

template <typename T>
size_t binaryTree<T>::size() const
{
    return sizeRecursive(root);
}

template <typename T>
size_t binaryTree<T>::sizeRecursive(treeNode<T>* node) const
{
    if (node == nullptr) return 0;
    return 1 + sizeRecursive(node->left) + sizeRecursive(node->right);
}

template <typename T>
template<typename Predicate>
typename binaryTree<T>::iterator binaryTree<T>::find_if(Predicate pred)
{
    treeNode<T>* found = findIfRecursive(root, pred);
    return iterator(found);
}

template <typename T>
template<typename Predicate>
treeNode<T>* binaryTree<T>::findIfRecursive(treeNode<T>* node, Predicate pred) const
{
    if (node == nullptr) return nullptr;

    if (pred(node->data)) return node;

    treeNode<T>* leftResult = findIfRecursive(node->left, pred);
    if (leftResult != nullptr) return leftResult;

    return findIfRecursive(node->right, pred);
}

template <typename T>
void binaryTree<T>::printTree() const
{
    printRecursive(root);
    std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::printRecursive(treeNode<T>* node, int depth) const
{
    if (node == nullptr) return;

    printRecursive(node->right, depth + 1);

    for (int i = 0; i < depth; ++i)
        std::cout << "   ";
    std::cout << node->data << std::endl;

    printRecursive(node->left, depth + 1);
}

// Вставляем реализацию get_algorithms() здесь
template <typename T>
tree_algorithms<T> binaryTree<T>::get_algorithms()
{
    return tree_algorithms<T>();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const binaryTree<T>& tree)
{
    // Создаем неконстантную копию для использования итераторов
    binaryTree<T>& non_const_tree = const_cast<binaryTree<T>&>(tree);

    // Используем алгоритмы для вывода
    auto alg = non_const_tree.get_algorithms();
    auto sorted = alg.get_sorted_ascending(non_const_tree.begin(), non_const_tree.end());
    for (const auto& item : sorted)
        os << item << " ";
    return os;
}


#endif // BINARY_TREE_TPP