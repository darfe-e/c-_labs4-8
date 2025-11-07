#include "..\headers\Article.h"

Article& Article::operator=(const Article& other)         // Оператор присваивания для класса Article
{
    if (this != &other)                                   // Проверка на самоприсваивание (защита от a = a)
    {
        this->title = other.title;                        // Копирование поля title из другого объекта Article
        this->authorName = other.authorName;              // Копирование поля authorName из другого объекта Article
    }
    return *this;                                         // Возврат ссылки на текущий объект для цепочки присваиваний
}

void Article::hat(std::ostream &os)                       // Метод для вывода заголовка таблицы статьи
{
    os << std::setw(12) << "Title" << std::setw(12) << "Auth\n";      // Вывод заголовков "Title" и "Auth" с шириной 8 символов каждый
}

template<typename T>
bool Article::operator== (T value)
{
    return (this->authorName == value
    || this->title == value);
}

bool Article::operator> (const Article& other)
{
    return this->title > other.title;
}

bool Article::operator< (const Article& other)
{
    return this->title < other.title;
}


std::ostream& operator<<(std::ostream& os, const Article& article)    // Дружественная функция - оператор вывода в поток
{
    os <<"\n"<< std::setw(12) << article.title << std::setw(12) <<  article.authorName;  // Вывод полей title и authorName с шириной 8 символов
    return os;                                                        // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>>(std::istream& is, Article& article)          // Дружественная функция - оператор ввода из потока
{
    std::cout << "Введите название статьи: ";                         // Приглашение для ввода названия статьи
    std::getline(is, article.title);                           // Чтение всей строки названия статьи из входного потока

    std::cout << "Введите имя автора: ";                             // Приглашение для ввода имени автора
    std::getline(is, article.authorName);                     // Чтение всей строки имени автора из входного потока

    return is;                                                      // Возврат потока для поддержки цепочки ввода
}

