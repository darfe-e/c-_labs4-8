#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include "LibraryCard.h"

class Catalog
{
protected:
    LibraryCard** libraryCards;    // Динамический массив указателей на объекты LibraryCard (двойной указатель)
    int cardsCount;                // Текущее количество карточек, хранящихся в каталоге
    int capacity;                  // Максимальная вместимость массива (емкость выделенной памяти)
public:
    Catalog () {libraryCards = nullptr; cardsCount = 0; capacity = 0;}  // Конструктор по умолчанию - инициализирует пустой каталог
    Catalog (const Catalog& other);                                     // Конструктор копирования
    virtual ~Catalog (){}                                               // Виртуальный деструктор для корректного удаления производных классов

    void addCard (LibraryCard* libraryCard);                            // Метод для добавления новой карточки в каталог
    virtual LibraryCard* search(const std::string& query) const = 0;    // Чисто виртуальный метод для поиска карточки по запросу
    Catalog& operator= (const Catalog& other);                          // Оператор присваивания

    virtual void menu ();                                               // Виртуальный метод для отображения меню каталога
};

#endif