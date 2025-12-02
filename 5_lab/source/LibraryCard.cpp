#include <sstream>
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

void LibraryCard::write_string_binary(std::fstream& fs, const std::string& str)
{
    size_t len = str.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0)
        fs.write(str.c_str(), len);
}

std::fstream& LibraryCard::read_string_binary(std::fstream& fs, std::string& str)
{
    size_t len;
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof())
    {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    str.resize(len);
    if (len > 0)
    {
        fs.read(&str[0], len);
        if (fs.fail() || fs.eof())
        {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }
    return fs;
}

std::fstream& operator<<(std::fstream& fs, const LibraryCard& card)
{
    LibraryCard::write_string_binary(fs, card.title);
    LibraryCard::write_string_binary(fs, card.author);
    LibraryCard::write_string_binary(fs, card.authorMark);
    LibraryCard::write_string_binary(fs, card.inventoryNumber);
    LibraryCard::write_string_binary(fs, card.thematicCode);

    return fs;
}

std::fstream& operator>>(std::fstream& fs, LibraryCard& card)
{
    LibraryCard::read_string_binary(fs, card.title);
    LibraryCard::read_string_binary(fs, card.author);
    LibraryCard::read_string_binary(fs, card.authorMark);
    LibraryCard::read_string_binary(fs, card.inventoryNumber);
    LibraryCard::read_string_binary(fs, card.thematicCode);

    return fs;
}

// Текстовый вывод
std::ofstream& operator<<(std::ofstream& ofs, const LibraryCard& card)
{
    ofs << card.title << "\n";
    ofs << card.author << "\n";
    ofs << card.authorMark << "\n";
    ofs << card.inventoryNumber << "\n";
    ofs << card.thematicCode << "\n";
    return ofs;
}

// Текстовый ввод
std::ifstream& operator>>(std::ifstream& ifs, LibraryCard& card)
{
    card.title = input_title(ifs);
    card.author = input_author(ifs);
    card.authorMark = input_single_word(ifs, "authorMark");
    card.inventoryNumber = input_word_with_hyphen(ifs, "inventoryNumber");
    card.thematicCode = input_single_word(ifs, "thematicCode");
    return ifs;
}

std::istream& operator>> (std::istream& is, LibraryCard& libraryCard)
{

    std::cout << "\nВведите название карты: ";           // Приглашение для ввода названия карточки
    libraryCard.title = input_title(is);              // Чтение всей строки названия карточки

    std::cout << "Введите имя автора: ";                 // Приглашение для ввода имени автора
    libraryCard.author = input_author(is);

    std::cout << "Авторский знак: ";                     // Приглашение для ввода авторского знака
    libraryCard.authorMark = input_single_word(is, "authorMark");      // Чтение всей строки авторского знака

    std::cout << "Инвентарный номер: ";                  // Приглашение для ввода инвентарного номера
    libraryCard.inventoryNumber = input_word_with_hyphen(is, "inventoryNumber"); // Чтение всей строки инвентарного номера

    std::cout << "Код по тематическому каталогу: ";      // Приглашение для ввода тематического кода
    libraryCard.thematicCode = input_single_word(is, "thematicCode");    // Чтение всей строки тематического кода

    return is;                                           // Возврат потока для поддержки цепочки ввода
}