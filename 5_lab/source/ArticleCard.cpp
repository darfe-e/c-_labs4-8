#include "..\headers\ArticleCard.h"
#include <iostream>

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

    // автоматически копирует все данные в карточку статьи
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