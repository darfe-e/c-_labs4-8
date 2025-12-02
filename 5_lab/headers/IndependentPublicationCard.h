#ifndef INDEPENDENTPUBLICATIONCARD_H
#define INDEPENDENTPUBLICATIONCARD_H

#include <iostream>
#include <string>
#include "LibraryCard.h"

class IndependentPublicationCard : public LibraryCard
{
protected:
    std::string publisher;          // Название издательства или издающей организации
    int yearOfPublication;          // Год публикации издания
    int circulation;                // Тираж издания (количество экземпляров)
    int pagesNamber;                // Количество страниц в издании

public:
    IndependentPublicationCard() : LibraryCard(), publisher(""), yearOfPublication(0),      // Конструктор по умолчанию - инициализирует все поля нулевыми значениями
                                   circulation(0), pagesNamber(0) {}

    IndependentPublicationCard (std::string publisher, int yearOfPublication, int circulation,  // Параметризированный конструктор со всеми полями
                                int pagesNamber, std::string title, std::string author, std::string authorMark,
                                std::string inventoryNumber, std::string thematicCode);

    IndependentPublicationCard (const IndependentPublicationCard& other);             // Конструктор копирования

    IndependentPublicationCard& operator= (const IndependentPublicationCard& other);  // Оператор присваивания
    bool operator==(const IndependentPublicationCard& other) const;
    bool operator==(const std::string& value) const;
    bool operator==(const char* value) const;
    bool operator==(int value) const;


    std::string getPublisher () const {return publisher;}                             // Геттер для названия издательства
    int getYearOfPublication () const {return yearOfPublication;}                     // Геттер для года публикации
    int getCirculation () const {return circulation;}                                 // Геттер для тиража
    int getPagesNamber () const {return pagesNamber;}                                 // Геттер для количества страниц

    void setPublisher (std::string publisher) { this->publisher = publisher; }                          // Сеттер для издательства
    void setYearOfPublication (int yearOfPublication) { this->yearOfPublication = yearOfPublication; }  // Сеттер для года публикации
    void setCirculation (int circulation){ this->circulation = circulation;}                            // Сеттер для тиража
    void setPagesNamber (int pagesNamber) { this->pagesNamber = pagesNamber; }                          // Сеттер для количества страниц

    friend std::ostream& operator<< (std::ostream& os, const IndependentPublicationCard& card);   // Дружественная функция для вывода в поток
    friend std::istream& operator>> (std::istream& is, IndependentPublicationCard& card);         // Дружественная функция для ввода из потока

    friend std::fstream& operator<<(std::fstream& fs, const IndependentPublicationCard& card);
    friend std::fstream& operator>>(std::fstream& fs, IndependentPublicationCard& card);
    friend std::ofstream& operator<<(std::ofstream& ofs, const IndependentPublicationCard& card);
    friend std::ifstream& operator>>(std::ifstream& ifs, IndependentPublicationCard& card);

    virtual void hat(std::ostream &os) override;          // Переопределенный виртуальный метод для вывода заголовка таблицы

    virtual void menu () override;                        // Переопределенный виртуальный метод для отображения меню


};

#endif