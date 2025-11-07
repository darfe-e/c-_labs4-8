#include "..\headers\ThematicCatalog.h"

LibraryCard* ThematicCatalog::search(const std::string& thematicCode) const
{
    LibraryCard* result;                                            // Объявление переменной для хранения найденной карточки - изначально содержит "мусор"

    for (int i = 0; i < cardsCount; i++)                            // Цикл по всем карточкам в каталоге от первой до последней
    {
        if (libraryCards[i]->getThematicCode() == thematicCode)     // Сравнение тематического кода текущей карточки с искомым
            result = libraryCards[i];                               // Присвоение указателя на найденную карточку в результат
    }

    return result;                                                  // Возврат результата поиска (может быть nullptr если ничего не найдено)
}

ThematicCatalog& ThematicCatalog::operator=(const ThematicCatalog& other)
{
    Catalog::operator=(other);                                        // Вызов оператора присваивания базового класса Catalog
    return *this;                                                     // Возврат ссылки на текущий объект для цепочки присваиваний
}

void ThematicCatalog::menu()
{
    Catalog::menu();                                                  // Вызов метода menu() базового класса Catalog
    std::cout << "\n2. Искать карточку по шифру (тематический код)."; // Добавление специфичного пункта меню для тематического каталога
}