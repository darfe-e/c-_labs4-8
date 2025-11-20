#ifndef ARTICLECOLLECTIONCARD_H
#define ARTICLECOLLECTIONCARD_H

#include "IndependentPublicationCard.h"
#include "ArticleCard.h"

class ArticleCollectionCard : public IndependentPublicationCard
{
private:
    int articleCount;                 // Текущее количество статей в сборнике (размер используемой части массива)
    ArticleCard* articleCards;        // Указатель на динамический массив объектов ArticleCard (не указателей, а самих объектов)
    int capacity;                     // Максимальная вместимость массива articleCards (общий размер выделенной памяти)

public:
    ArticleCollectionCard();          // Конструктор по умолчанию - инициализирует пустой сборник статей

    ArticleCollectionCard(                                                        // Основной параметризированный конструктор
            std::string title, std::string author, std::string authorMark,        // Параметры базовой информации: название, автор, авторский знак
            std::string inventoryNumber, std::string thematicCode,                // Параметры: инвентарный номер, тематический код
            std::string publisher, int year, int circulation, int pagesNumber);   // Параметры публикации: издательство, год, тираж, страницы

    ArticleCollectionCard(const ArticleCollectionCard& other);                    // Конструктор копирования (deep copy)
    ~ArticleCollectionCard();                                                     // Деструктор - освобождает динамическую память

    void addArticleCard(const ArticleCard& articleCard);                          // Метод для добавления новой карточки статьи в сборник

    ArticleCard* getArticleCards() const { return articleCards; }                 // Геттер: возвращает указатель на массив карточек статей
    int getArticleCount() const { return articleCount; }                          // Геттер: возвращает текущее количество статей в сборнике

    ArticleCollectionCard& operator=(const ArticleCollectionCard& other);         // Оператор присваивания (copy assignment)
    template<typename T>
    friend bool operator== (ArticleCollectionCard& card, T value);

    friend std::ostream& operator<<(std::ostream& os, const ArticleCollectionCard& card);  // Дружественная функция: вывод объекта в поток
    friend std::istream& operator>>(std::istream& is, ArticleCollectionCard& card);        // Дружественная функция: ввод объекта из потока

    friend std::fstream& operator<<(std::fstream& fs, const ArticleCollectionCard& card);
    friend std::fstream& operator>>(std::fstream& fs, ArticleCollectionCard& card);
    friend std::ofstream& operator<<(std::ofstream& ofs, const ArticleCollectionCard& card);
    friend std::ifstream& operator>>(std::ifstream& ifs, ArticleCollectionCard& card);

    void hat (std::ostream &os) override;                          // Переопределенный метод: вывод заголовков таблицы для сборника статей
    virtual void menu () override;                                 // Переопределенный метод: отображение меню операций для сборника статей
};

#endif