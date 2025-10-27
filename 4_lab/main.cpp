#include <iostream>
#include "..\3_lab\c_plus_labs\.vscode\inheritence\BookCard.h"
#include "headers/binryTree.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);                          // Установка кодовой страницы UTF-8 для корректного отображения русских символов

    binaryTree<BookCard> tree;
    Article* article1 = new Article("Faust", "Gette");
    BookCard card1 ("aut2", "inv2", "22-i", "Publ2", 2025, 10000, 141, *article1);   // Создание карточки статьи на основе независимой публикации

    Article* article2 = new Article("Portrait", "Oscar W");
    BookCard card2 ("aut3", "inv3", "33-e", "Publ3", 1921, 30000, 377, *article2);

    tree.push(card1);
    tree.push(card2);

    card1.hat(std::cout);
    tree.printTree();

    std::cin.get();

    delete article1;
    delete article2;

//    binaryTree<int> tree;
//
//    tree.push(1);
//    tree.push(2);
//    tree.push(3);
//
//    tree.printTree();
//    std::cin.get();

    return 0;
}
