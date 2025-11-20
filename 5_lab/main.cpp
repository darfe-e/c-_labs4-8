#include "library_manager.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int mainChoice;

    std::cout << "=== Система управления библиотечными карточками ===\n";

    while (true)
    {
        std::cout << "\n\nНажмите Enter для продолжения...";
        std::cin.get(); system("cls");

        std::cout << "\nГлавное меню:\n";
        std::cout << "\n1. Работа с деревом ArticleCollectionCard\n";
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
        std::cin.get(); system("cls");

        switch (mainChoice)
        {
            case 1:
            {
                LibraryManager<ArticleCollectionCard> manager("ArticleCollectionCard");
                manager.run();
                break;
            }
            case 2:
            {
                LibraryManager<BookCard> manager("BookCard");
                manager.run();
                break;
            }
            case 3:
            {
                LibraryManager<ArticleCard> manager("ArticleCard");
                manager.run();
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