#include "library_manager.h"
#include "D:\study\2_year\pnaiavy\3_lab\c_plus_labs\.vscode\inheritence\IndependentPublicationCard.h"
#include "D:\study\2_year\pnaiavy\3_lab\c_plus_labs\.vscode\inheritence\BookCard.h"
#include "D:\study\2_year\pnaiavy\3_lab\c_plus_labs\.vscode\inheritence\ArticleCard.h"
#include "headers/binryTree.h"
#include "headers/ArticleCollectionCard.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int mainChoice;

    std::cout << "=== Система управления библиотечными карточками ===\n";

    while (true)
    {
        std::cout << "\n\nНажмите Enter для продолжения...";  // Пауза перед очисткой экрана
        std::cin.get(); system("cls");               // Ожидание нажатия Enter, Очистка консоли (Windows команда)

        std::cout << "\nГлавное меню:\n";
        std::cout << "\n1. Работа с деревом ArticleCollectionTree\n";
        std::cout << "2. Работа с деревом BookCard\n";
        std::cout << "3. Работа с деревом ArticleCard\n";
        std::cout << "4. Выход\n\n";
        std::cout << "Введите ваш выбор: ";

        if (!(std::cin >> mainChoice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Неверный ввод. Пожалуйста, введите число.\n";
            continue;
        }
        std::cin.get(); system("cls");               // Ожидание нажатия Enter, Очистка консоли (Windows команда)

        switch (mainChoice)
        {
            case 1:
            {
                auto comparator = choose_comparator<ArticleCollectionCard>("ArticleCollectionCard");
                binaryTree<ArticleCollectionCard> ArticleCollectionTree(comparator);
                handleTreeOperations(ArticleCollectionTree, "ArticleCollectionCard");
                break;
            }
            case 2:
            {
                auto comparator = choose_comparator<BookCard>("BookCard");
                binaryTree<BookCard> BookTree(comparator);
                handleTreeOperations(BookTree, "BookCard");
                break;
            }
            case 3:
            {
                auto comparator = choose_comparator<ArticleCard>("ArticleCard");
                binaryTree<ArticleCard> ArticleTree(comparator);
                handleTreeOperations(ArticleTree, "ArticleCard");
                break;
            }
            case 4:
            {
                std::cout<<"\nЗавершение программы...";
                std::cin.get();
                return 0;
            }
            default:
                std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до 4.\n";
        }
    }
}