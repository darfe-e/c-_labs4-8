#ifndef INC_5_LAB_FUNC_WITH_EXC_H
#define INC_5_LAB_FUNC_WITH_EXC_H

#include <string>
#include <iostream>
#include "headers/author_validation_exception.h"
#include "headers/title_validation_exception.h"
#include "headers/word_validation_exception.h"
#include "headers/number_validation_exception.h"
#include "headers/year_validation_exception.h"

// Коды ошибок
enum ErrorCodes
{
    AUTHOR_EMPTY = 1001,                    // Автор пустой
    AUTHOR_INVALID_CHARS = 1002,            // Недопустимые символы в имени автора
    AUTHOR_CAPITALIZATION = 1003,           // Ошибка капитализации в имени автора
    AUTHOR_TOO_LONG = 1004,                 // Имя автора слишком длинное

    TITLE_EMPTY = 2001,                     // Название пустое
    TITLE_INVALID_CHARS = 2002,             // Недопустимые символы в названии
    TITLE_CAPITALIZATION = 2003,            // Ошибка капитализации в названии
    TITLE_NUMBER_POSITION = 2004,           // Неправильная позиция цифр в названии

    WORD_EMPTY = 3001,                      // Слово пустое
    WORD_INVALID_CHARS = 3002,              // Недопустимые символы в слове
    WORD_HYPHEN_POSITION = 3003,            // Неправильная позиция дефиса

    NUMBER_EMPTY = 4001,                    // Число пустое
    NUMBER_INVALID = 4002,                  // Неправильный числовой формат
    NUMBER_TOO_LONG = 4003,                 // Число слишком длинное

    YEAR_EMPTY = 5001,                      // Год пустой
    YEAR_INVALID = 5002,                    // Неправильный формат года
    YEAR_OUT_OF_RANGE = 5003                // Год вне допустимого диапазона
};

// Функции валидации строк
std::string input_author(std::istream& is);                                                             // Ввод и валидация автора
std::string input_title(std::istream& is);                                                              // Ввод и валидация названия
std::string input_single_word(std::istream& is, const std::string& field_name);                         // Ввод и валидация одного слова
std::string input_word_with_hyphen(std::istream& is, const std::string& field_name);                    // Ввод и валидация слова с дефисом

// Функции валидации чисел
int input_year(std::istream& is);                                                                       // Ввод и валидация года
int input_circulation(std::istream& is);                                                                // Ввод и валидация тиража
int input_pages(std::istream& is);                                                                      // Ввод и валидация количества страниц


#endif //INC_5_LAB_FUNC_WITH_EXC_H
