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

std::fstream& operator<<(std::fstream& fs, const Article& article)
{
    size_t len = article.getTitle().length();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    fs.write(article.getTitle().c_str(), len);

    len = article.getAuthorName().length();
    fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
    fs.write(article.getAuthorName().c_str(), len);

    return fs;
}

// Бинарный ввод для Article
std::fstream& operator>>(std::fstream& fs, Article& article)
{
    size_t len;
    char* buffer;

    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    fs.read(buffer, len);
    buffer[len] = '\0';
    article.setTitle(buffer);
    delete[] buffer;

    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    fs.read(buffer, len);
    buffer[len] = '\0';
    article.setAuthorName(buffer);
    delete[] buffer;

    return fs;
}

// Текстовый вывод для Article
std::ofstream& operator<<(std::ofstream& ofs, const Article& article)
{
    ofs << article.getTitle() << "\n";
    ofs << article.getAuthorName() << "\n";
    return ofs;
}

// Текстовый ввод для Article
std::ifstream& operator>>(std::ifstream& ifs, Article& article)
{
    std::string title, author;
    std::getline(ifs, title);
    std::getline(ifs, author);
    article.setTitle(title);
    article.setAuthorName(author);
    return ifs;
}