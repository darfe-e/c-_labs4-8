#ifndef LIBRARYCARD_H
#define LIBRARYCARD_H

#include <iostream>
#include <string>
#include <iomanip>
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\exceptions/func_with_exc.h"

class LibraryCard
{
protected:
    std::string author;              // Фамилия и инициалы автора произведения
    std::string title;               // Название произведения
    std::string authorMark;          // Авторский знак (буквенно-цифровой код)
    std::string inventoryNumber;     // Инвентарный номер в библиотеке
    std::string thematicCode;        // Тематический код (шифр)

public:
    LibraryCard() : title(""), author(""), authorMark(""),        // Конструктор по умолчанию - инициализирует все поля пустыми строками
                    inventoryNumber(""), thematicCode(""){}

    LibraryCard(std::string title, std::string author, std::string authorMark, // Параметризированный конструктор
                std::string inventoryNumber, std::string thematicCode);

    LibraryCard(const LibraryCard& other);                              // Конструктор копирования
    virtual ~LibraryCard(){}                                            // Виртуальный деструктор для корректного удаления производных классов

    LibraryCard& operator= (const LibraryCard& other);                  // Оператор присваивания
    bool operator==(const LibraryCard& other) const;                    // Сравнение с другим объектом
    bool operator==(const std::string& value) const;                    // Сравнение со string
    bool operator==(const char* value) const;                           // Сравнение с const char*


    bool operator> (const LibraryCard& other) const {return this->title > other.title;}
    bool operator< (const LibraryCard& other) const {return this->title < other.title;}

    std::string getAuthor () const {return author;}                     // Геттер для автора - возвращает строку по значению
    std::string getTitle () const {return title;}                       // Геттер для названия - возвращает строку по значению
    std::string getAuthorMark () const {return authorMark;}             // Геттер для авторского знака - возвращает строку по значению
    std::string getInventoryNumber () const {return inventoryNumber;}   // Геттер для инвентарного номера
    std::string getThematicCode () const {return thematicCode;}         // Геттер для тематического кода

    void setAuthor(const std::string& newAuthor) { author = newAuthor; }                                      // Сеттер для автора - принимает константную ссылку
    void setTitle(const std::string& newTitle) { title = newTitle; }                                          // Сеттер для названия - принимает константную ссылку
    void setAuthorMark(const std::string& newAuthorMark) { authorMark = newAuthorMark; }                      // Сеттер для авторского знака
    void setInventoryNumber(const std::string& newInventoryNumber) { inventoryNumber = newInventoryNumber; }  // Сеттер для инвентарного номера
    void setThematicCode(const std::string& newThematicCode) { thematicCode = newThematicCode; }              // Сеттер для тематического кода

    std::string getInformstionForSerch (){return author + ' ' + title;}                                       // Метод для поиска - объединяет автора и название через пробел

    virtual void hat (std::ostream& os);                                                 // Виртуальный метод для вывода заголовка таблицы
    virtual void menu ();                                                                // Виртуальный метод для отображения меню

    friend std::ostream& operator<< (std::ostream& os, const LibraryCard& libraryCard);  // Дружественная функция для вывода в поток
    friend std::istream& operator>> (std::istream& is, LibraryCard& libraryCard);        // Дружественная функция для ввода из потока

};


#endif