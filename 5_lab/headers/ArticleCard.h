#ifndef ARTICLECARD_H
#define ARTICLECARD_H

#include "LibraryCard.h"
#include "Article.h"
#include "IndependentPublicationCard.h"

class ArticleCard : public LibraryCard
{
private:
    Article article;                               // Объект статьи, хранящий содержание (композиция - копия статьи)
    IndependentPublicationCard* publicationCard;   // Указатель на объект самостоятельного издания (агрегация - внешний объект)

public:
    ArticleCard() : LibraryCard(), article(), publicationCard(nullptr) {}     // Конструктор по умолчанию - инициализирует все поля нулевыми значениями
    ArticleCard(IndependentPublicationCard* publicationCard);                 // Конструктор с параметром - указатель на издание

    ArticleCard(const ArticleCard& other);                                    // Конструктор копирования (deep copy)
    ~ArticleCard() {}                                                         // Деструктор (пустой, так как нет динамической памяти для удаления)

    Article getArticle() const { return article; }                                       // Геттер: возвращает копию объекта статьи
    IndependentPublicationCard& getPublicationCard() const { return *publicationCard; }  // Геттер: возвращает ссылку на объект издания

    void setArticle(const Article& newArticle) { this->article = newArticle; };// Сеттер: устанавливает новую статью (копирование)
    void setPublicationCard(IndependentPublicationCard* newPublicationCard);  // Сеттер: устанавливает указатель на издание

    ArticleCard& operator=(const ArticleCard& other);                         // Оператор присваивания (copy assignment)
    template<typename T>
    friend bool operator== (ArticleCard& card, T value);

    friend std::ostream& operator<<(std::ostream& os, ArticleCard& card);     // Дружественная функция: вывод объекта в поток
    friend std::istream& operator>>(std::istream& is, ArticleCard& card);     // Дружественная функция: ввод объекта из потока

    virtual void menu () override;                                            // Переопределенный метод: отображение меню операций для карточки статьи
    void hat (std::ostream &os) override;                                     // Переопределение метода отоюражения шапки таблицы
};

#endif