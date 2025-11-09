#ifndef INC_4_LAB_BINRYTREE_H                    // Защита от многократного включения
#define INC_4_LAB_BINRYTREE_H                    // Определение макроса для данного заголовочного файла

#include "treeNode.h"                             // Включение заголовочного файла для узла дерева
#include <iostream>                               // Включение библиотеки ввода-вывода
#include <type_traits>                            // Включение библиотеки для работы с типами
#include <vector>                                 // Включение библиотеки для работы с векторами
#include <functional>

template <typename T>                             // Шаблонный класс бинарного дерева
class binaryTree
{
private:
    treeNode<T>* root;                                  // Указатель на корневой узел дерева
    std::function<bool(const T&, const T&)> comparator; // Компаратор

public:
    binaryTree() : root(nullptr),
            comparator([](const T& a, const T& b) { return a < b; }) {}
    binaryTree(std::function<bool(const T&, const T&)> comp)
            : root(nullptr), comparator(comp) {}
    ~binaryTree();                                // Деструктор для очистки памяти

    void push(T value);                           // Метод для добавления элемента в дерево
    treeNode<T>* remove(T value);                 // Метод для удаления элемента из дерева
    void printTree();                             // Метод для вывода дерева

    template<typename SV>                         // Шаблонный метод для поиска по любому типу
    treeNode<T>* find(const SV& value);           // Поиск элемента в дереве

    std::vector<T> getSortedAscending();          // Получение элементов в отсортированном порядке (возрастание)
    std::vector<T> getSortedDescending();         // Получение элементов в отсортированном порядке (убывание)
    void printSortedAscending();                  // Вывод элементов по возрастанию
    void printSortedDescending();                 // Вывод элементов по убыванию

    template<typename Predicate>                  // Шаблонный метод для поиска по предикату
    treeNode<T>* find_if(Predicate pred);         // Поиск элемента, удовлетворяющего условию

    template<typename U>                          // Объявление дружественной функции вывода
    friend std::ostream& operator<<(std::ostream& os, const binaryTree<U>& tree); // Перегрузка оператора вывода

private:
    void insert(treeNode<T>* node, treeNode<T>* newNode);     // Вспомогательный метод для вставки узла
    treeNode<T>* removeRecursive(treeNode<T>* node, T value); // Рекурсивное удаление узла
    treeNode<T>* findMin(treeNode<T>* node);                  // Поиск минимального элемента в поддереве
    void printRecursive(treeNode<T>* node) const;             // Рекурсивный вывод дерева (константный метод)

    template<typename SV>                                     // Шаблонный рекурсивный поиск
    treeNode<T>* findRecursive(treeNode<T>* node, const SV& value); // Рекурсивный поиск элемента

    template<typename Predicate>                              // Шаблонный рекурсивный поиск по предикату
    treeNode<T>* findIfRecursive(treeNode<T>* node, Predicate pred); // Рекурсивный поиск по условию

    void clearRecursive(treeNode<T>* node);                   // Рекурсивная очистка памяти дерева

    void inOrderTraversal(treeNode<T>* node, std::vector<T>& result);        // Обход дерева в порядке возрастания
    void reverseInOrderTraversal(treeNode<T>* node, std::vector<T>& result); // Обход дерева в порядке убывания
};

#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\source\binryTree.tpp"
#endif //INC_4_LAB_BINRYTREE_H                    // Конец защитного блока