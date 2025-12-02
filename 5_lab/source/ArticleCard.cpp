#include "..\headers\ArticleCard.h"
#include <iostream>
#include <chrono>

ArticleCard:: ArticleCard(IndependentPublicationCard* publicationCard)            // Конструктор с параметром - указатель на издание
        : LibraryCard(*dynamic_cast<LibraryCard*>(publicationCard)),              // Инициализация базового класса: тематический код берется из издания
          article(publicationCard->getTitle(), publicationCard->getAuthor()),     // Инициализация статьи: название и автор из издания
          publicationCard(publicationCard)                                        // Инициализация указателя на издание переданным значением
{}

ArticleCard::ArticleCard(const ArticleCard& other)          // Конструктор копирования
        : LibraryCard(other)                                // Вызов конструктора копирования базового класса LibraryCard
        , article(other.article)                            // Временная инициализация статьи пустым объектом (исправлено бы на article(other.article))
        , publicationCard(other.publicationCard)            // Копирование указателя на издание из другого объекта (поверхностное копирование)
{}


void ArticleCard::setPublicationCard(IndependentPublicationCard* newPublicationCard)  // Метод установки указателя на издание
{
    publicationCard = newPublicationCard;                                             // Присвоение нового значения указателю на издание
}

ArticleCard& ArticleCard::operator=(const ArticleCard& other)                         // Оператор присваивания
{
    if (this != &other)                          // Проверка на самоприсваивание (защита от a = a)
    {
        LibraryCard::operator=(other);           // Вызов оператора присваивания базового класса LibraryCard
        article = other.article;                 // Копирование объекта статьи через оператор присваивания класса Article
        publicationCard = other.publicationCard; // Копирование указателя на издание (поверхностное копирование)
    }
    return *this;                                // Возврат ссылки на текущий объект для цепочки присваиваний
}

std::ostream& operator<<(std::ostream& os, ArticleCard& card)  // Дружественная функция - оператор вывода в поток
{
    os << *card.publicationCard;                               // Разыменование указателя и вывод объекта издания через его оператор <<
    return os;                                                 // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>>(std::istream& is, ArticleCard& card)     // Дружественная функция - оператор ввода из потока
{
    IndependentPublicationCard tempPublication;                   // Создаем временное издание для ввода данных

    std::cout << "\n\n=== Ввод данных издания ===" << std::endl;  // Заголовок для этапа ввода издания
    is >> tempPublication;                                        // Ввод данных издания через оператор >> IndependentPublicationCard

    card.setAuthor(tempPublication.getAuthor());                  // Установка автора из временного издания
    card.setTitle(tempPublication.getTitle());                    // Установка названия из временного издания
    card.setAuthorMark(tempPublication.getAuthorMark());          // Установка авторского знака из временного издания
    card.setInventoryNumber(tempPublication.getInventoryNumber());// Установка инвентарного номера из временного издания
    card.setThematicCode(tempPublication.getThematicCode());      // Установка тематического кода из временного издания

    if (card.publicationCard != nullptr) delete card.publicationCard;              // Освобождение памяти предыдущего издания, если оно существует
    card.publicationCard = new IndependentPublicationCard(tempPublication);        // Создание нового издания в куче

    Article tempArticle(tempPublication.getTitle(), tempPublication.getAuthor());  // Создание статьи с названием и автором из издания
    card.setArticle(tempArticle);                                                  // Установка созданной статьи в карточку

    std::cout << "\nArticleCard создан автоматически из данных издания!" << std::endl;  // Информационное сообщение

    return is;                                                        // Возврат потока для поддержки цепочки ввода
}

template<typename T>
bool operator== (ArticleCard& card, T value)
{
    return (static_cast<LibraryCard&>(card) == value);
}

void ArticleCard::menu()                                              // Метод отображения меню операций
{
    LibraryCard::menu();                                              // Вызов метода menu базового класса для отображения базовых пунктов
    std::cout << "\n5. Get other values (article, publicationCard)";  // Дополнительный пункт меню: получение статьи и издания
    std::cout << "\n6. Set other values (article, publicationCard)";  // Дополнительный пункт меню: установка статьи и издания
}

void ArticleCard::hat(std::ostream &os)                               // Переопределение метода отоюражения шапки таблицы
{
    publicationCard->hat(os);
}

std::fstream& operator<<(std::fstream& fs, const ArticleCard& card)
{
    if (card.publicationCard != nullptr)
    {
        fs << static_cast<const LibraryCard&>(*card.publicationCard);
        LibraryCard::write_string_binary(fs, card.publicationCard->getPublisher());

        int year = card.publicationCard->getYearOfPublication();
        int circulation = card.publicationCard->getCirculation();
        int pages = card.publicationCard->getPagesNamber();

        fs.write(reinterpret_cast<const char*>(&year), sizeof(year));
        fs.write(reinterpret_cast<const char*>(&circulation), sizeof(circulation));
        fs.write(reinterpret_cast<const char*>(&pages), sizeof(pages));
    }
    else
    {
        fs << static_cast<const LibraryCard&>(card);

        LibraryCard::write_string_binary(fs, "");  // пустой publisher

        int zero = 0;
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    }

    return fs;
}

// Бинарный ввод
std::fstream& operator>>(std::fstream& fs, ArticleCard& card)
{
    LibraryCard tempLibraryCard;
    fs >> tempLibraryCard;
    if (fs.fail()) return fs;

    std::string publisher;
    if (!LibraryCard::read_string_binary(fs, publisher))
    {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    int yearOfPublication, circulation, pagesNamber;
    auto read_numeric = [&](auto& value) -> bool
    {
        fs.read(reinterpret_cast<char*>(&value), sizeof(value));
        return !(fs.fail() || fs.eof());
    };

    if (!read_numeric(yearOfPublication) ||
        !read_numeric(circulation) ||
        !read_numeric(pagesNamber)) {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    card.setAuthor(tempLibraryCard.getAuthor());
    card.setTitle(tempLibraryCard.getTitle());
    card.setAuthorMark(tempLibraryCard.getAuthorMark());
    card.setInventoryNumber(tempLibraryCard.getInventoryNumber());
    card.setThematicCode(tempLibraryCard.getThematicCode());

    if (card.publicationCard != nullptr)
        delete card.publicationCard;

    if (!publisher.empty() || yearOfPublication != 0 || circulation != 0 || pagesNamber != 0)
    {
        card.publicationCard = new IndependentPublicationCard(
                publisher, yearOfPublication, circulation, pagesNamber,
                tempLibraryCard.getTitle(), tempLibraryCard.getAuthor(),
                tempLibraryCard.getAuthorMark(), tempLibraryCard.getInventoryNumber(),
                tempLibraryCard.getThematicCode()
        );
    }
    else
        card.publicationCard = nullptr;

    return fs;
}

// Текстовый вывод
std::ofstream& operator<<(std::ofstream& ofs, const ArticleCard& card)
{
    if (card.publicationCard != nullptr)
    {
        ofs << static_cast<const LibraryCard&>(*card.publicationCard);
        ofs << card.publicationCard->getPublisher() << "\n";
        ofs << card.publicationCard->getYearOfPublication() << "\n";
        ofs << card.publicationCard->getCirculation() << "\n";
        ofs << card.publicationCard->getPagesNamber() << "\n";
    }
    else
    {
        // Если publicationCard отсутствует, записываем только базовые поля
        ofs << static_cast<const LibraryCard&>(card);
        ofs << "\n"; // пустой publisher
        ofs << "0\n"; // yearOfPublication = 0
        ofs << "0\n"; // circulation = 0
        ofs << "0\n"; // pagesNamber = 0
    }

    return ofs;
}

// Текстовый ввод
std::ifstream& operator>>(std::ifstream& ifs, ArticleCard& card)
{
    IndependentPublicationCard tempPublication;
    ifs >> static_cast<LibraryCard&>(tempPublication);

    tempPublication.setPublisher(input_title(ifs));           // Ввод и валидация издательства
    tempPublication.setYearOfPublication(input_num(ifs, 1500, 2025));    // Ввод и валидация года издания
    tempPublication.setCirculation(input_num(ifs, 1, 10000000));   // Ввод и валидация тиража
    tempPublication.setPagesNamber(input_num(ifs, 1, 10000));         // Ввод и валидация количества страниц

    card.setAuthor(tempPublication.getAuthor());
    card.setTitle(tempPublication.getTitle());
    card.setAuthorMark(tempPublication.getAuthorMark());
    card.setInventoryNumber(tempPublication.getInventoryNumber());
    card.setThematicCode(tempPublication.getThematicCode());

    if (card.publicationCard != nullptr)
        delete card.publicationCard;
    card.publicationCard = new IndependentPublicationCard(tempPublication);

    return ifs;
}