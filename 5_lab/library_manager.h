#ifndef INC_4_LAB_ADDITIONAL_H                                                  // Защита от многократного включения
#define INC_4_LAB_ADDITIONAL_H                                                  // Определение макроса для данного заголовочного файла

#include "headers/IndependentPublicationCard.h"                              // Включение заголовка класса карточек публикаций
#include "headers/binryTree.h"                                               // Включение заголовка бинарного дерева


void main_menu_options();                                                       // Объявление функции вывода главного меню
template<typename T>
void handleTreeOperations(binaryTree<T>& tree, const std::string& treeName);

template<typename T>
treeNode<T>* search_by_template(binaryTree<T>& tree, const T& search_template);
template<typename T>
T create_search_template();
bool has_criterias(auto search_template, const std::string& treeName);
template<typename T>
bool search_chosen(const T& templateIndependent, const T& independentCard) ;
template<typename T>
std::function<bool(const T&, const T&)> choose_comparator(const std::string& treeName);

#endif //INC_4_LAB_ADDITIONAL_H                                                 // Конец защитного блока