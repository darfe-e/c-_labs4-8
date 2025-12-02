#include <chrono>
#include "..\headers\IndependentPublicationCard.h"

IndependentPublicationCard::IndependentPublicationCard(
        std::string publisher,
        int yearOfPublication,
        int circulation,
        int pagesNamber,

        std::string title,
        std::string author,
        std::string authorMark,
        std::string inventoryNumber,
        std::string thematicCode)

        : LibraryCard(title, author, authorMark, inventoryNumber, thematicCode)  // Вызов конструктора базового класса LibraryCard с параметрами
        , publisher(publisher)                                                   // Инициализация поля publisher значением параметра
        , yearOfPublication(yearOfPublication)                                   // Инициализация поля yearOfPublication значением параметра
        , circulation(circulation)                                               // Инициализация поля circulation значением параметра
        , pagesNamber (pagesNamber)                                              // Инициализация поля pagesNamber значением параметра
{}

IndependentPublicationCard::IndependentPublicationCard(const IndependentPublicationCard& other)
        :LibraryCard(other),                                                      // Вызов конструктора копирования базового класса
         publisher(other.publisher),                                              // Копирование поля publisher из другого объекта
         yearOfPublication(other.yearOfPublication),                              // Копирование поля yearOfPublication из другого объекта
         circulation(other.circulation),                                          // Копирование поля circulation из другого объекта
         pagesNamber(other.pagesNamber)                                           // Копирование поля pagesNamber из другого объекта
{}

IndependentPublicationCard& IndependentPublicationCard::operator=(const IndependentPublicationCard& other)
{
    if (this != &other)                                   // Проверка на самоприсваивание - если объект не присваивается сам себе
    {
        this->publisher = other.publisher;                // Копирование поля publisher из другого объекта
        this->yearOfPublication = other.yearOfPublication;// Копирование поля yearOfPublication из другого объекта
        this->circulation = other.circulation;            // Копирование поля circulation из другого объекта
        this->pagesNamber = other.pagesNamber;            // Копирование поля pagesNamber из другого объекта

        LibraryCard::operator=(other);                    // Вызов оператора присваивания базового класса LibraryCard
    }
    return *this;                                         // Возврат ссылки на текущий объект для цепочки присваиваний
}

void IndependentPublicationCard::hat(std::ostream &os)
{
    LibraryCard::hat(os);                                           // Вызов метода hat базового класса для вывода базовых заголовков

    os << std::setw(12) << "Publ."<< std::setw(12) << "Publ.year"      // Вывод заголовка "Publ." (Издательство) с шириной 12 символов
       << std::setw(12)<<"Circ."<< std::setw(12)<<"PagesNum";          // Вывод заголовков "Circ." (Тираж) и "PagesNum" (Кол-во страниц)
}

std::ostream& operator<< (std::ostream& os, const IndependentPublicationCard& card)
{
    os << static_cast<const LibraryCard&>(card)                                      // Преобразование к базовому классу и вывод базовой части через оператор << LibraryCard
       << std::setw(12)<< card.publisher << std::setw(12) << card.yearOfPublication  // Вывод поля publisher и yearOfPublication с шириной 12
       << std::setw(12)<< card.circulation << std::setw(12)<< card.pagesNamber;      // Вывод поля circulation и pagesNamber с шириной 12
    return os;                                                                       // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>> (std::istream& is, IndependentPublicationCard& card)
{
    is >> static_cast<LibraryCard&>(card);

    std::cout << "Введите издательство: ";
    card.publisher = input_author(is);

    std::cout << "Введите год издания: ";
    card.yearOfPublication = input_num(is, 1500, 2025);

    std::cout << "Введите тираж: ";
    card.circulation = input_num(is, 1, 10000000);

    std::cout << "Введите количество страниц: ";
    card.pagesNamber = input_num(is, 1, 10000);

    return is;
}

void IndependentPublicationCard::menu ()
{
    LibraryCard::menu();                                // Вызов метода menu базового класса для вывода базовых пунктов меню
    std::cout << "\n5. Получить другие значения (publisher, yearOfPublication, circulation, pagesNamber).";  // Дополнительный пункт меню для получения значений
    std::cout << "\n6. Установить другие значения (publisher, yearOfPublication, circulation, pagesNamber)."; // Дополнительный пункт меню для установки значений
}

bool IndependentPublicationCard::operator==(const IndependentPublicationCard& other) const
{
    return (LibraryCard::operator==(other) &&
            this->publisher == other.publisher &&
            this->yearOfPublication == other.yearOfPublication &&
            this->circulation == other.circulation &&
            this->pagesNamber == other.pagesNamber);
}

// Сравнение со string
bool IndependentPublicationCard::operator==(const std::string& value) const
{
    return (LibraryCard::operator==(value) ||
            publisher == value);
}

bool IndependentPublicationCard::operator==(const char* value) const
{
    return operator==(std::string(value));
}

bool IndependentPublicationCard::operator==(int value) const
{
    return (yearOfPublication == value ||
            circulation == value ||
            pagesNamber == value);
}

std::fstream& operator<<(std::fstream& fs, const IndependentPublicationCard& card)
{
    fs << static_cast<const LibraryCard&>(card);

    LibraryCard::write_string_binary(fs, card.publisher);

    fs.write(reinterpret_cast<const char*>(&card.yearOfPublication), sizeof(card.yearOfPublication));
    fs.write(reinterpret_cast<const char*>(&card.circulation), sizeof(card.circulation));
    fs.write(reinterpret_cast<const char*>(&card.pagesNamber), sizeof(card.pagesNamber));

    return fs;
}

// Бинарный ввод
std::fstream& operator>>(std::fstream& fs, IndependentPublicationCard& card)
{
    fs >> static_cast<LibraryCard&>(card);
    if (fs.fail()) return fs;

    if (!LibraryCard::read_string_binary(fs, card.publisher))
    {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    auto read_numeric = [&](auto& value) -> bool
    {
        fs.read(reinterpret_cast<char*>(&value), sizeof(value));
        return !(fs.fail() || fs.eof());
    };

    if (!read_numeric(card.yearOfPublication) ||
        !read_numeric(card.circulation) ||
        !read_numeric(card.pagesNamber))
    {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    return fs;
}

std::ofstream& operator<<(std::ofstream& ofs, const IndependentPublicationCard& card)
{
    ofs << static_cast<const LibraryCard&>(card);

    ofs << card.publisher << "\n";
    ofs << card.yearOfPublication << "\n";
    ofs << card.circulation << "\n";
    ofs << card.pagesNamber << "\n";

    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, IndependentPublicationCard& card)
{
    ifs >> static_cast<LibraryCard&>(card);

    card.publisher = input_author(ifs);                                                              // Ввод и валидация издательства
    card.yearOfPublication = input_num(ifs, 1500, 2025);                                                        // Ввод и валидация года издания
    card.circulation = input_num(ifs, 1, 10000000);                                                       // Ввод и валидация тиража
    card.pagesNamber = input_num(ifs, 1, 10000);


    return ifs;
}