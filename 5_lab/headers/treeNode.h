#ifndef INC_4_LAB_TREENODE_H                     // Защита от многократного включения
#define INC_4_LAB_TREENODE_H                     // Определение макроса для данного заголовочного файла
#include "binryTree.h"

template <typename T>
class binaryTree;

template <typename T>                            // Шаблонный класс узла дерева
class treeNode
{
    friend class binaryTree<T>;
private:
    T data;                                      // Данные, хранящиеся в узле
    treeNode* left;                              // Указатель на левый дочерний узел
    treeNode* right;                             // Указатель на правый дочерний узел

public:
    treeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}  // Конструктор, инициализирующий узел

    T getData() { return this->data; };          // Метод для получения данных из узла
};

#endif //INC_4_LAB_TREENODE_H                    // Конец защитного блока