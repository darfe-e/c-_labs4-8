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

std::istream& operator>> (std::istream& is, LibraryCard& libraryCard)
{
    std::cout << "\nВведите название карты: ";           // Приглашение для ввода названия карточки
    libraryCard.title = input_title(is);           // Чтение всей строки названия карточки

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
// Бинарный вывод
std::fstream& operator<<(std::fstream& fs, const LibraryCard& card)
{
    // Записываем длину каждой строки + данные
    size_t len = card.title.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        fs.write(card.title.c_str(), len);
    }

    len = card.author.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        fs.write(card.author.c_str(), len);
    }

    len = card.authorMark.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        fs.write(card.authorMark.c_str(), len);
    }

    len = card.inventoryNumber.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        fs.write(card.inventoryNumber.c_str(), len);
    }

    len = card.thematicCode.size();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        fs.write(card.thematicCode.c_str(), len);
    }

    return fs;
}

// Бинарный ввод
std::fstream& operator>>(std::fstream& fs, LibraryCard& card)
{
    size_t len;

    // Проверяем, есть ли данные для чтения
    if (fs.peek() == EOF) {
        fs.setstate(std::ios::eofbit);
        return fs;
    }

    // Читаем title
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }
    card.title.resize(len);
    if (len > 0) {
        fs.read(&card.title[0], len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }

    // Читаем author
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }
    card.author.resize(len);
    if (len > 0) {
        fs.read(&card.author[0], len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }

    // Читаем authorMark
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }
    card.authorMark.resize(len);
    if (len > 0) {
        fs.read(&card.authorMark[0], len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }

    // Читаем inventoryNumber
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }
    card.inventoryNumber.resize(len);
    if (len > 0) {
        fs.read(&card.inventoryNumber[0], len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }

    // Читаем thematicCode
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }
    card.thematicCode.resize(len);
    if (len > 0) {
        fs.read(&card.thematicCode[0], len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
    }

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
    std::getline(ifs, card.title);
    std::getline(ifs, card.author);
    std::getline(ifs, card.authorMark);
    std::getline(ifs, card.inventoryNumber);
    std::getline(ifs, card.thematicCode);
    return ifs;
}