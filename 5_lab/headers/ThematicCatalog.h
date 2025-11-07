#ifndef THEMATICCATALOG_H
#define THEMATICCATALOG_H

#include "Catalog.h"
#include <iostream>

class ThematicCatalog : public Catalog                                          // Класс для поиска карточки по шифру
{
public:
    ThematicCatalog() : Catalog() {}                                            // Конструктор
    ThematicCatalog(const ThematicCatalog& other): Catalog(other) {}            // Конструктор копирования
    ~ThematicCatalog(){}                                                        // Деструктор
    
    LibraryCard* search(const std::string& thematicCode) const override;        // Поиск по шифру (тематическому коду)
    
    ThematicCatalog& operator=(const ThematicCatalog& other);                   // Оператор присваивания

    void menu () override;                                                      // Изменение базового виртуального метода меню
};

#endif