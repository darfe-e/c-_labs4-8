#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class Article
{
    std::string title;        // Название статьи
    std::string authorName;   // Имя автора статьи

public:
    Article() : title(""), authorName(""){}                                             // Конструктор по умолчанию - инициализирует пустыми строками
    Article(std::string title, std::string authorName) : title(title), authorName(authorName){}  // Параметризированный конструктор
    Article(const Article& other) : title(other.title), authorName(other.authorName){}           // Конструктор копирования

    std::string getTitle() const { return title; }                                  // Геттер для названия статьи - возвращает по значению
    std::string getAuthorName() const { return authorName; }                        // Геттер для имени автора - возвращает по значению

    void setAuthorName (std::string authorName) { this->authorName = authorName; }  // Сеттер для имени автора
    void setTitle (std::string title) { this->title = title; }                      // Сеттер для названия статьи

    Article& operator= (const Article& other);                                      // Оператор присваивания

    template<typename T>
    bool operator== (T value);

    bool operator> (const Article& other);
    bool operator< (const Article& other);

    friend std::ostream& operator<< (std::ostream& os, const Article& article);     // Дружественная функция вывода в поток
    friend std::istream& operator>>(std::istream& is, Article& article);            // Дружественная функция ввода из потока

    friend std::fstream& operator<<(std::fstream& fs, const Article& card);
    friend std::fstream& operator>>(std::fstream& fs, Article& card);
    friend std::ofstream& operator<<(std::ofstream& ofs, const Article& card);
    friend std::ifstream& operator>>(std::ifstream& ifs, Article& card);

    void hat(std::ostream &os);                                                     // Метод для вывода заголовка таблицы статьи
};

#endif