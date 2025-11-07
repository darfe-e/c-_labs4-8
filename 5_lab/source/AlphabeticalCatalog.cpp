#include "..\headers\AlphabeticalCatalog.h"
#include <algorithm>

LibraryCard* AlphabeticalCatalog::search(const std::string& authorAndTitle) const  // Метод поиска карточки по автору и названию
{
    LibraryCard* result = nullptr;                     // Инициализация результата как nullptr (карточка не найдена)

    for (int i = 0; i < cardsCount; i++)               // Цикл по всем карточкам в каталоге от первой до последней
    {
        std::string infForSerch = libraryCards[i]->getInformstionForSerch();  // Получение строки для поиска из текущей карточки
        if (infForSerch == authorAndTitle) result = libraryCards[i];          // Если строка поиска совпала с запросом, сохраняем указатель на карточку
    }

    return result;                                                            // Возврат найденной карточки или nullptr если ничего не найдено
}

AlphabeticalCatalog& AlphabeticalCatalog::operator=(const AlphabeticalCatalog& other)  // Оператор присваивания
{
    Catalog::operator=(other);                         // Вызов оператора присваивания базового класса Catalog
    return *this;                                      // Возврат ссылки на текущий объект для цепочки присваиваний
}

void AlphabeticalCatalog::menu()                       // Метод отображения меню алфавитного каталога
{
    Catalog::menu();                                   // Вызов метода menu базового класса Catalog для отображения общих пунктов

    std::cout << "\n2. Искать карточку по автору и названию.";  // Добавление специфичного пункта меню для алфавитного каталога
}