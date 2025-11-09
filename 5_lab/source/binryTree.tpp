#ifndef BINRYTREE_TPP                            // Защита от многократного включения
#define BINRYTREE_TPP                            // Определение макроса для файла реализации

#include <iostream>                              // Включение библиотеки ввода-вывода

template <typename T>
binaryTree<T>::~binaryTree()
{
    clearRecursive(root);                    // Рекурсивная очистка всех узлов дерева
    root = nullptr;                               // Обнуление корневого указателя
}

template <typename T>
void binaryTree<T>::clearRecursive(treeNode<T>* node)
{
    if (node == nullptr) return;                  // Базовый случай рекурсии - пустой узел

    clearRecursive(node->left);                   // Рекурсивная очистка левого поддерева
    clearRecursive(node->right);                  // Рекурсивная очистка правого поддерева

    delete node;                                  // Освобождение памяти текущего узла
}

template <typename T>
template <typename SV>
treeNode<T>* binaryTree<T>::find(const SV& value)
{
    return findRecursive(root, value);            // Запуск рекурсивного поиска от корня
}

template <typename T>
template <typename SV>
treeNode<T>* binaryTree<T>::findRecursive(treeNode<T>* node, const SV& value)
{
    if (!node) return nullptr;                    // Базовый случай - узел не найден
    if (node->data == value) return node;         // Элемент найден в текущем узле

    treeNode<T>* left = findRecursive(node->left, value);  // Поиск в левом поддереве
    if (left) return left;                        // Если найден в левом поддереве - возвращаем
    return findRecursive(node->right, value);     // Поиск в правом поддереве
}

template <typename T>
void binaryTree<T>::insert(treeNode<T>* node, treeNode<T>* newNode)
{
    if (comparator(newNode->getData(), node->getData()))
    {
        if (node->left != nullptr)
            insert(node->left, newNode);
        else
            node->left = newNode;
    }
    else if (comparator(node->getData(), newNode->getData()))
    {
        if (node->right != nullptr)
            insert(node->right, newNode);
        else
            node->right = newNode;
    }
    else {
        delete newNode; // Дубликат
    }
}

template <typename T>
void binaryTree<T>::push(T value) {
    treeNode<T>* newNode = new treeNode<T>(value); // Создание нового узла

    if (root == nullptr) root = newNode;           // Если дерево пустое - новый узел становится корнем
    else insert(root, newNode);               // Иначе - вставка в нужное место
}

template <typename T>
treeNode<T>* binaryTree<T>::remove(T value)
{
    root = removeRecursive(root, value);     // Запуск рекурсивного удаления от корня
    return root;                                   // Возврат обновленного корня
}

template <typename T>
treeNode<T>* binaryTree<T>::removeRecursive(treeNode<T>* node, T value)
{
    if (node == nullptr) return nullptr;          // Базовый случай - узел не найден

    if (value < node->data) node->left = removeRecursive(node->left, value);        // Поиск в левом поддереве
    else if (value > node->data) node->right = removeRecursive(node->right, value); // Поиск в правом поддереве
    else                                          // Элемент найден
    {
        if (node->left == nullptr)                // Случай 1: нет левого потомка
        {
            treeNode<T>* temp = node->right;      // Сохраняем правого потомка
            delete node;                          // Удаляем текущий узел
            return temp;                          // Возвращаем правого потомка
        }
        else if (node->right == nullptr)          // Случай 2: нет правого потомка
        {
            treeNode<T>* temp = node->left;       // Сохраняем левого потомка
            delete node;                          // Удаляем текущий узел
            return temp;                          // Возвращаем левого потомка
        }

        // Случай 3: есть оба потомка
        treeNode<T>* successor = findMin(node->right);  // Находим минимальный в правом поддереве
        node->data = successor->data;                   // Заменяем данные на данные преемника
        node->right = removeRecursive(node->right, successor->data); // Удаляем дубликат преемника
    }
    return node;                                                     // Возврат текущего узла
}

template <typename T>
treeNode<T>* binaryTree<T>::findMin(treeNode<T>* node)
{
    while (node != nullptr && node->left != nullptr)  // Пока есть левый потомок
        node = node->left;                            // Двигаемся влево

    return node;                                      // Возвращаем самый левый узел
}

template <typename T>
void binaryTree<T>::printTree()
{
    std::cout << "Содержимое дерева (pre-order): ";  // Заголовок вывода
    printRecursive(root);                      // Запуск рекурсивного вывода
    std::cout << std::endl;                         // Перевод строки
}

template <typename T>
void binaryTree<T>::printRecursive(treeNode<T>* node) const
{
    if (node == nullptr) return;                        // Базовый случай - пустой узел

    std::cout << node->data << " ";                     // Вывод данных текущего узла (pre-order)
    printRecursive(node->left);                   // Рекурсивный вывод левого поддерева
    printRecursive(node->right);                  // Рекурсивный вывод правого поддерева
}

template <typename T>
template <typename Predicate>
treeNode<T>* binaryTree<T>::findIfRecursive(treeNode<T>* node, Predicate pred)
{
    if (!node) return nullptr;                    // Базовый случай - узел не найден
    if (pred(node->data)) return node;            // Проверка предиката для текущего узла

    treeNode<T>* leftResult = findIfRecursive(node->left, pred);  // Поиск в левом поддереве
    if (leftResult) return leftResult;            // Если найден в левом поддереве - возвращаем

    return findIfRecursive(node->right, pred);    // Поиск в правом поддереве
}

template <typename T>
void binaryTree<T>::inOrderTraversal(treeNode<T>* node, std::vector<T>& result)
{
    if (node == nullptr) return;                        // Базовый случай - пустой узел

    inOrderTraversal(node->left, result);      // Рекурсия в левое поддерево
    result.push_back(node->data);                       // Добавление текущего узла в результат
    inOrderTraversal(node->right, result);     // Рекурсия в правое поддерево
}

template <typename T>
void binaryTree<T>::reverseInOrderTraversal(treeNode<T>* node, std::vector<T>& result)  // Reverse in-order обход (правый-корень-левый) для убывающего порядка
{
    if (node == nullptr) return;                           // Базовый случай - пустой узел

    reverseInOrderTraversal(node->right, result); // Рекурсия в правое поддерево
    result.push_back(node->data);                          // Добавление текущего узла в результат
    reverseInOrderTraversal(node->left, result);  // Рекурсия в левое поддерево
}

template <typename T>
std::vector<T> binaryTree<T>::getSortedAscending()// Получить отсортированный вектор по возрастанию
{
    std::vector<T> result;                        // Создание вектора для результатов
    inOrderTraversal(root, result);      // Заполнение вектора in-order обходом
    return result;                                // Возврат отсортированного вектора
}

template <typename T>
std::vector<T> binaryTree<T>::getSortedDescending()// Получить отсортированный вектор по убыванию
{
    std::vector<T> result;                         // Создание вектора для результатов
    reverseInOrderTraversal(root, result);// Заполнение вектора reverse in-order обходом
    return result;                                 // Возврат отсортированного вектора
}

template <typename T>
void binaryTree<T>::printSortedAscending()        // Вывод отсортированного по возрастанию
{
    std::vector<T> sorted = getSortedAscending(); // Получение отсортированного вектора
    std::cout << "Отсортировано по возрастанию: ";// Заголовок вывода
    for (const auto& item : sorted) {             // Цикл по всем элементам вектора
        std::cout << item << " ";                 // Вывод каждого элемента
    }
    std::cout << std::endl;                       // Перевод строки
}

template <typename T>
void binaryTree<T>::printSortedDescending()       // Вывод отсортированного по убыванию
{
    std::vector<T> sorted = getSortedDescending();// Получение отсортированного вектора
    std::cout << "Отсортировано по убыванию: ";   // Заголовок вывода
    for (const auto& item : sorted) {             // Цикл по всем элементам вектора
        std::cout << item << " ";                 // Вывод каждого элемента
    }
    std::cout << std::endl;                       // Перевод строки
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const binaryTree<T>& tree)
{
    tree.printRecursive(tree.root);               // Вывод дерева через рекурсивный метод
    std::cout << std::endl;                       // Перевод строки

    return os;                                    // Возврат потока вывода
}

template <typename T>
template <typename Predicate>
treeNode<T>* binaryTree<T>::find_if(Predicate pred)
{
    return findIfRecursive(root, pred);           // Запуск рекурсивного поиска по предикату
}

#endif // BINRYTREE_TPP                           // Конец защитного блока