#include "..\headers\ArticleCollectionCard.h"

ArticleCollectionCard::ArticleCollectionCard() : IndependentPublicationCard(),     // Конструктор по умолчанию - вызов базового конструктора
        articleCards(nullptr)
        , articleCount(0)                                                          // Инициализация счетчика статей нулем
        , capacity(0)                                                              // Инициализация вместимости массива нулем
{}

ArticleCollectionCard::ArticleCollectionCard                                        // Основной параметризированный конструктор
        (
                std::string title, std::string author, std::string authorMark,      // Параметры: название, автор, авторский знак
                std::string inventoryNumber, std::string thematicCode,              // Параметры: инвентарный номер, тематический код
                std::string publisher, int year, int circulation, int pagesNumber)  // Параметры: издательство, год, тираж, количество страниц
        : IndependentPublicationCard(publisher, year, circulation, pagesNumber,     // Вызов конструктора базового класса с параметрами
             title, author, authorMark, inventoryNumber, thematicCode)              // Передача параметров в базовый конструктор
        , articleCards(nullptr)                                                     // Инициализация указателя на массив карточек как nullptr
        , articleCount(0)                                                           // Инициализация счетчика статей нулем
        , capacity(0)                                                               // Инициализация вместимости массива нулем
{}

ArticleCollectionCard::ArticleCollectionCard(const ArticleCollectionCard& other)  // Конструктор копирования
        : IndependentPublicationCard(other)                        // Вызов конструктора копирования базового класса
        , articleCards(nullptr)                                    // Временная инициализация указателя как nullptr
        , articleCount(0)                                          // Временная инициализация счетчика нулем
        , capacity(0)                                              // Временная инициализация вместимости нулем
{
    for (int i = 0; i < other.articleCount; i++)                  // Цикл по всем карточкам статей в исходном объекте
        addArticleCard(other.articleCards[i]);                    // Добавление копии каждой карточки статьи в новый объект
}

ArticleCollectionCard::~ArticleCollectionCard()                   // Деструктор
{
    delete[] articleCards;                                        // Освобождение памяти, выделенной под массив карточек статей
}

void ArticleCollectionCard::addArticleCard(const ArticleCard& articleCard) // Метод добавления карточки статьи в сборник
{
    if (articleCount >= capacity)                              // Проверка: достигнут ли предел вместимости массива
    {
        int newCapacity = (capacity == 0) ? 5 : capacity * 2;  // Вычисление новой вместимости: 5 если пусто, иначе удвоение
        ArticleCard* newArray = new ArticleCard[newCapacity];  // Создание нового массива карточек с новой вместимостью

        for (int i = 0; i < articleCount; i++)                 // Цикл копирования существующих карточек в новый массив
            newArray[i] = articleCards[i];                     // Копирование каждой карточки через оператор присваивания

        delete[] articleCards;                                 // Освобождение памяти старого массива карточек
        articleCards = newArray;                               // Присвоение указателя на новый массив
        capacity = newCapacity;                                // Обновление значения вместимости
    }

    articleCards[articleCount] = articleCard;                  // Добавление новой карточки в конец массива
    articleCount++;                                            // Увеличение счетчика карточек после добавления
}

ArticleCollectionCard& ArticleCollectionCard::operator=(const ArticleCollectionCard& other) // Оператор присваивания
{
    if (this != &other)                                         // Проверка на самоприсваивание (защита от a = a)
    {
        IndependentPublicationCard::operator=(other);           // Вызов оператора присваивания базового класса

        delete[] articleCards;                                  // Освобождение памяти текущего массива карточек

        articleCount = 0;                                       // Сброс счетчика карточек до нуля
        capacity = 0;                                           // Сброс вместимости до нуля
        articleCards = nullptr;                                 // Установка указателя в nullptr

        for (int i = 0; i < other.articleCount; i++)            // Цикл по всем карточкам в исходном объекте
            addArticleCard(other.articleCards[i]);              // Добавление копии каждой карточки в текущий объект
    }
    return *this;                                               // Возврат ссылки на текущий объект для цепочки присваиваний
}

void ArticleCollectionCard::hat(std::ostream &os)               // Метод вывода заголовков таблицы
{
    IndependentPublicationCard::hat(os);                     // Вызов метода hat базового класса для вывода базовых заголовков
    os << std::setw(12) << "Art.num.";                          // Добавление заголовка для количества статей с шириной 12 символов
}

std::ostream& operator<<(std::ostream& os, const ArticleCollectionCard& card) // Дружественная функция - оператор вывода
{
    os << static_cast<const IndependentPublicationCard&>(card);               // Вывод базовой части через преобразование к базовому классу
    os << std::setw(12) << card.articleCount;                                 // Вывод количества статей в сборнике с шириной 12 символов

    return os;                                                                // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>>(std::istream& is, ArticleCollectionCard& card) // Дружественная функция - оператор ввода
{
    is >> static_cast<IndependentPublicationCard&>(card);     // Ввод базовой части через преобразование к базовому классу
    return is;                                                // Возврат потока для поддержки цепочки ввода
}

template<typename T>
bool operator== (ArticleCollectionCard& card, T value)
{
    return (static_cast<IndependentPublicationCard&>(card) == value);
}


void ArticleCollectionCard::menu()                            // Метод отображения меню операций
{
    IndependentPublicationCard::menu();                       // Вызов метода menu базового класса для отображения базовых пунктов
    std::cout << "\n7. Получить количство карт статей;";      // Дополнительный пункт меню: получение количества карточек статей
    std::cout << "\n8. Получить карты статей;";               // Дополнительный пункт меню: получение массива карточек статей
    std::cout << "\n9. Добавить карточку статьи.";            // Дополнительный пункт меню: добавление новой карточки статьи
}

// Бинарный вывод
std::fstream& operator<<(std::fstream& fs, const ArticleCollectionCard& card)
{
    // Сначала вызываем оператор базового класса
    fs << static_cast<const IndependentPublicationCard&>(card);
    if (fs.fail()) return fs;

    // Затем записываем массив статей
    fs.write(reinterpret_cast<const char*>(&card.articleCount), sizeof(card.articleCount));

    for (int i = 0; i < card.articleCount; i++) {

        const ArticleCard& articleCard = card.articleCards[i];
        fs << articleCard;  // Теперь компилятор понимает тип
        if (fs.fail()) return fs;
    }

    return fs;
}

// Бинарный ввод
std::fstream& operator>>(std::fstream& fs, ArticleCollectionCard& card)
{
    // Сначала вызываем оператор базового класса
    fs >> static_cast<IndependentPublicationCard&>(card);
    if (fs.fail()) return fs;

    // Затем читаем количество статей
    int count;
    fs.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (fs.fail() || fs.eof() || count < 0 || count > 10000) { // разумные пределы
        fs.setstate(std::ios::failbit);
        return fs;
    }

    // Освобождаем старую память если нужно
    delete[] card.articleCards;

    // Выделяем новую память
    card.articleCards = new ArticleCard[count];
    card.articleCount = count;
    card.capacity = count;

    for (int i = 0; i < count; i++) {
        fs >> card.articleCards[i];
        if (fs.fail()) {
            // В случае ошибки освобождаем память и выходим
            delete[] card.articleCards;
            card.articleCards = nullptr;
            card.articleCount = 0;
            card.capacity = 0;
            return fs;
        }
    }

    return fs;
}

// Текстовый вывод
std::ofstream& operator<<(std::ofstream& ofs, const ArticleCollectionCard& card)
{
    // Сначала вызываем оператор базового класса
    ofs << static_cast<const IndependentPublicationCard&>(card);

    // Затем записываем массив статей
    ofs << card.articleCount << "\n";
    for (int i = 0; i < card.articleCount; i++) {
        const ArticleCard& articleCard = card.articleCards[i];
        ofs << articleCard;  // Теперь компилятор понимает тип
    }

    return ofs;
}

// Текстовый ввод
std::ifstream& operator>>(std::ifstream& ifs, ArticleCollectionCard& card)
{
    // Сначала вызываем оператор базового класса
    ifs >> static_cast<IndependentPublicationCard&>(card);

    // Затем читаем массив статей
    int count;
    ifs >> count;
    ifs.ignore(); // пропускаем \n

    // Освобождаем старую память если нужно
    delete[] card.articleCards;

    // Выделяем новую память
    card.articleCards = new ArticleCard[count];
    card.articleCount = count;
    card.capacity = count;

    for (int i = 0; i < count; i++) {
        ifs >> card.articleCards[i];
    }

    return ifs;
}