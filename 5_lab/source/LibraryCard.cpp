#include "..\headers\LibraryCard.h"

LibraryCard::LibraryCard(std::string title, std::string author, std::string authorMark,
                         std::string inventoryNumber,std::string thematicCode) : title(title), author(author),
                         authorMark(authorMark), inventoryNumber(inventoryNumber), thematicCode(thematicCode)
{}                                                                                                  // Тело конструктора пустое - вся инициализация в списке инициализации

LibraryCard::LibraryCard(const LibraryCard& other) : title(other.title), author(other.author),
                        authorMark(other.authorMark), inventoryNumber(other.inventoryNumber),
                        thematicCode(other.thematicCode)
{}                                                                                                  // Конструктор копирования - копирует все поля из другого объекта

LibraryCard& LibraryCard::operator=(const LibraryCard& other)
{
    if (this != &other)                                   // Проверка на самоприсваивание - если объект не присваивается сам себе
    {
        this->title = other.title;                        // Копирование поля title из другого объекта
        this->author = other.author;                      // Копирование поля author из другого объекта
        this->authorMark = other.authorMark;              // Копирование поля authorMark из другого объекта
        this->inventoryNumber = other.inventoryNumber;    // Копирование поля inventoryNumber из другого объекта
        this->thematicCode = other.thematicCode;          // Копирование поля thematicCode из другого объекта
    }
    return *this;                                         // Возврат ссылки на текущий объект для цепочки присваиваний
}

void LibraryCard::hat(std::ostream& os)
{
    os << "\n"                                           // Переход на новую строку для начала вывода
       << std::left                                      // Установка выравнивания по левому краю для всех полей
       << std::setw(10) << "Title"                       // Вывод заголовка "Title" с шириной 10 символов
       << std::setw(10) << "Auth"                        // Вывод заголовка "Auth" с шириной 10 символов
       << std::setw(10) << "Au.sign"                     // Вывод заголовка "Au.sign" с шириной 10 символов
       << std::setw(10) << "Inv.num."                    // Вывод заголовка "Inv.num." с шириной 10 символов
       << std::setw(10) << "Th.code";                    // Вывод заголовка "Th.code" с шириной 10 символов
}


std::ostream& operator<< (std::ostream& os, const LibraryCard& libraryCard)
{
    os << "\n"                                           // Переход на новую строку для начала вывода данных
       << std::left                                      // Установка выравнивания по левому краю для всех полей
       << std::setw(10) << libraryCard.title             // Вывод поля title с шириной 10 символов
       << std::setw(10) << libraryCard.author            // Вывод поля author с шириной 10 символов
       << std::setw(10) << libraryCard.authorMark        // Вывод поля authorMark с шириной 10 символов
       << std::setw(10) << libraryCard.inventoryNumber   // Вывод поля inventoryNumber с шириной 10 символов
       << std::setw(10) << libraryCard.thematicCode;     // Вывод поля thematicCode с шириной 10 символов
    return os;                                           // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>> (std::istream& is, LibraryCard& libraryCard)
{
    std::cout << "\nВведите название карты: ";           // Приглашение для ввода названия карточки
    std::getline(is, libraryCard.title);           // Чтение всей строки названия карточки

    std::cout << "Введите имя автора: ";                 // Приглашение для ввода имени автора
    std::getline(is, libraryCard.author);          // Чтение всей строки имени автора

    std::cout << "Авторский знак: ";                     // Приглашение для ввода авторского знака
    std::getline(is, libraryCard.authorMark);      // Чтение всей строки авторского знака

    std::cout << "Инвентарный номер: ";                  // Приглашение для ввода инвентарного номера
    std::getline(is, libraryCard.inventoryNumber); // Чтение всей строки инвентарного номера

    std::cout << "Код по тематическому каталогу: ";      // Приглашение для ввода тематического кода
    std::getline(is, libraryCard.thematicCode);    // Чтение всей строки тематического кода

    return is;                                           // Возврат потока для поддержки цепочки ввода
}

void LibraryCard::menu()
{
    std::cout<<"\nLibraryCard menu:\n";                                                                  // Заголовок меню LibraryCard
    std::cout<<"\n1. Получить значение (author, title, authorMark, InventoryNumber or ThematicCode);"    // Пункт меню 1 - получение значений
             <<"\n2. Установить значение (author, title, authorMark, InventoryNumber or ThematicCode);"  // Пункт меню 2 - установка значений
             <<"\n3. Показать информацию об объекте;"            // Пункт меню 3 - отображение информации об объекте
             <<"\n4. Получить информацию для поиска.";           // Пункт меню 4 - получение информации для поиска
}



// Сравнение с другим объектом LibraryCard
bool LibraryCard::operator==(const LibraryCard& other) const
{
    return (this->author == other.author &&
            this->title == other.title &&
            this->authorMark == other.authorMark &&
            this->inventoryNumber == other.inventoryNumber &&
            this->thematicCode == other.thematicCode);
}

// Сравнение со string
bool LibraryCard::operator==(const std::string& value) const
{
    return (author == value ||
            title == value ||
            authorMark == value ||
            inventoryNumber == value ||
            thematicCode == value);
}

// Сравнение с const char*
bool LibraryCard::operator==(const char* value) const
{
    return operator==(std::string(value));
}