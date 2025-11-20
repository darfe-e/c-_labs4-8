#ifndef BOOKCARD_H
#define BOOKCARD_H

#include "IndependentPublicationCard.h"
#include "Article.h"

class BookCard : public IndependentPublicationCard
{
private:
    Article article;    // Объект статьи, которая представляет содержание книги (композиция)

public:
    BookCard();                                                                   // Конструктор по умолчанию
    BookCard(                                                           // Основной параметризированный конструктор
            std::string authorMark,                                               // Параметр: авторский знак книги
            std::string inventoryNumber, std::string thematicCode,                // Параметры: инвентарный номер и тематический код
            std::string publisher, int year, int circulation, int pagesNumber,    // Параметры: издательство, год, тираж, кол-во страниц
            const Article& article);                                              // Параметр: объект статьи (содержание книги)

    BookCard(const BookCard& other);                                    // Конструктор копирования (deep copy)
    ~BookCard(){}                                                       // Деструктор (пустой, так как нет динамической памяти)

    Article getArticle() const { return article; }                      // Геттер: возвращает копию объекта статьи

    void setArticle(const Article& newArticle) { article = newArticle; }// Сеттер: устанавливает новую статью (копирование)

    BookCard& operator=(const BookCard& other);                         // Оператор присваивания (copy assignment)
    bool operator==(const BookCard& other) const;
    bool operator==(const std::string& value) const;
    bool operator==(const char* value) const;
    bool operator==(int value) const;


    friend std::fstream& operator<<(std::fstream& fs, const BookCard& card);
    friend std::fstream& operator>>(std::fstream& fs, BookCard& card);
    friend std::ofstream& operator<<(std::ofstream& ofs, const BookCard& card);
    friend std::ifstream& operator>>(std::ifstream& ifs, BookCard& card);

    friend std::ostream& operator<<(std::ostream& os, BookCard& card);  // Дружественная функция: вывод объекта в поток
    friend std::istream& operator>>(std::istream& is, BookCard& card);  // Дружественная функция: ввод объекта из потока

    void hat (std::ostream &os) override;                               // Переопределенный метод: вывод заголовков таблицы
    void menu () override;                                              // Переопределенный метод: отображение меню операций
};

#endif