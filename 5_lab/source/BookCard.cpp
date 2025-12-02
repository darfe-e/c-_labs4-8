#include "..\headers\BookCard.h"
#include <iostream>

BookCard::BookCard()                                                   // Конструктор по умолчанию
        : IndependentPublicationCard()                                 // Вызов конструктора по умолчанию базового класса IndependentPublicationCard
        , article()                                                    // Вызов конструктора по умолчанию для объекта article класса Article
{}

BookCard::BookCard(                                                              // Основной параметризированный конструктор
        std::string authorMark,                                                  // Параметр: авторский знак книги
        std::string inventoryNumber, std::string thematicCode,                   // Параметры: инвентарный номер и тематический код
        std::string publisher, int year, int circulation, int pagesNumber,       // Параметры: издательство, год издания, тираж, количество страниц
        const Article& article)                                                  // Параметр: константная ссылка на объект статьи
        : IndependentPublicationCard(publisher, year, circulation, pagesNumber,  // Вызов конструктора базового класса с параметрами
             article.getTitle(), article.getAuthorName(), authorMark, inventoryNumber, thematicCode)  // Использование данных статьи для базовой части
        , article(article)                                                       // Инициализация поля article копированием переданного объекта
{}

BookCard::BookCard(const BookCard& other)                             // Конструктор копирования
        : IndependentPublicationCard(other)                           // Вызов конструктора копирования базового класса
        , article(other.article)                                      // Копирование объекта статьи из другого объекта BookCard
{}

BookCard& BookCard::operator=(const BookCard& other)                  // Оператор присваивания
{
    if (this != &other)                                               // Проверка на самоприсваивание (защита от a = a)
    {
        IndependentPublicationCard::operator=(other);                 // Вызов оператора присваивания базового класса
        article = other.article;                                      // Копирование объекта статьи из другого объекта
    }
    return *this;                                                     // Возврат ссылки на текущий объект для цепочки присваиваний
}

void BookCard::hat(std::ostream &os)
{
    IndependentPublicationCard::hat(os);                           // Вызов метода hat базового класса без добавления новых заголовков
}

std::ostream& operator<<(std::ostream& os, BookCard& card)            // Дружественная функция - оператор вывода в поток
{
    os << static_cast<IndependentPublicationCard&>(card);             // Преобразование к базовому классу и вывод через его оператор <<
    return os;                                                        // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>>(std::istream& is, BookCard& card)            // Дружественная функция - оператор ввода из потока
{
    is >> static_cast<IndependentPublicationCard&>(card);             // Преобразование к базовому классу и ввод через его оператор >>

    Article bookContent(card.getTitle(), card.getAuthor());           // Создание объекта статьи на основе названия и автора из карточки
    card.setArticle(bookContent);                                     // Установка созданной статьи в объект карточки

    std::cout << "\nСодержание книги создано автоматически из названия и автора" << std::endl;  // Информационное сообщение

    return is;                                                        // Возврат потока для поддержки цепочки ввода
}


void BookCard::menu ()
{
    IndependentPublicationCard::menu();                              // Вызов метода menu базового класса для отображения базовых пунктов
    std::cout << "\n7. Получить статью;";                            // Дополнительный пункт меню для получения статьи
    std::cout << "\n8. Установить статью.";                          // Дополнительный пункт меню для установки статьи
}

bool BookCard::operator==(const BookCard& other) const
{
    return (IndependentPublicationCard::operator==(other));
}

bool BookCard::operator==(const std::string& value) const
{
    return IndependentPublicationCard::operator==(value);
}

bool BookCard::operator==(const char* value) const
{
    return IndependentPublicationCard::operator==(value);
}

bool BookCard::operator==(int value) const
{
    return IndependentPublicationCard::operator==(value);
}


std::fstream& operator<<(std::fstream& fs, const BookCard& card)
{
    fs << static_cast<const IndependentPublicationCard&>(card);
    return fs;
}

std::fstream& operator>>(std::fstream& fs, BookCard& card)
{
    fs >> static_cast<IndependentPublicationCard&>(card);
    return fs;
}

std::ofstream& operator<<(std::ofstream& ofs, const BookCard& card)
{
    ofs << static_cast<const IndependentPublicationCard&>(card);
    return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, BookCard& card)
{
    ifs >> static_cast<IndependentPublicationCard&>(card);
    return ifs;
}