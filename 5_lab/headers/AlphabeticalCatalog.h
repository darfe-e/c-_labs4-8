#ifndef ALPHABETICALCATALOG_H
#define ALPHABETICALCATALOG_H

#include "Catalog.h"
#include <iostream>

class AlphabeticalCatalog : public Catalog
{
public:
    AlphabeticalCatalog() : Catalog() {}                                       // Конструктор по умолчанию - вызывает конструктор базового класса Catalog
    AlphabeticalCatalog(const AlphabeticalCatalog& other): Catalog(other) {}   // Конструктор копирования - вызывает конструктор копирования базового класса
    ~AlphabeticalCatalog(){}                                                   // Деструктор - пустой, так как нет дополнительных ресурсов для освобождения

    LibraryCard* search(const std::string& authorAndTitle) const override;     // Переопределенный виртуальный метод поиска по автору и названию

    AlphabeticalCatalog& operator=(const AlphabeticalCatalog& other);  // Оператор присваивания для алфавитного каталога
    void menu () override;                                             // Переопределенный метод отображения меню алфавитного каталога
};

#endif