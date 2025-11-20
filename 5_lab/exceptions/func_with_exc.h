#ifndef INC_5_LAB_FUNC_WITH_EXC_H
#define INC_5_LAB_FUNC_WITH_EXC_H

#include <string>                           // Для работы со строками
#include <iostream>                         // Для потоков ввода-вывода
#include <fstream>
#include <vector>
#include "headers/input_exceptions/author_validation_exception.h" // Заголовок исключения для автора
#include "headers/input_exceptions/title_validation_exception.h"  // Заголовок исключения для названия
#include "headers/input_exceptions/word_validation_exception.h"   // Заголовок исключения для слов
#include "headers/input_exceptions/number_validation_exception.h" // Заголовок исключения для чисел
#include "headers/input_exceptions/year_validation_exception.h"   // Заголовок исключения для года

#include "headers/file_exceptions/file_access_exception .h"
#include "headers/file_exceptions/file_exception .h"
#include "headers/file_exceptions/file_format_exception .h"
#include "headers/file_exceptions/file_open_exception .h"
#include "headers/file_exceptions/file_read_exception.h"
#include "headers/file_exceptions/file_write_exception .h"

// Коды ошибок
enum ErrorCodes                             // Перечисление кодов ошибок валидации
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
    YEAR_OUT_OF_RANGE = 5003,                // Год вне допустимого диапазона

    FILE_OPEN_ERROR = 6001,
    FILE_READ_ERROR = 6002,
    FILE_WRITE_ERROR = 6003,
    FILE_FORMAT_ERROR = 6004,
    FILE_ACCESS_ERROR = 6005,
    FILE_MISMATCH_ERROR = 6006
};

// Функции валидации строк
std::string input_author(std::istream& is);                                        // Ввод и валидация автора
std::string input_title(std::istream& is);                                         // Ввод и валидация названия
std::string input_single_word(std::istream& is, const std::string& field_name);    // Ввод и валидация одного слова
std::string input_word_with_hyphen(std::istream& is, const std::string& field_name);// Ввод и валидация слова с дефисом

// Функции валидации чисел
int input_year(std::istream& is);                                                   // Ввод и валидация года
int input_circulation(std::istream& is);                                            // Ввод и валидация тиража
int input_pages(std::istream& is);

// Функции для работы с текстовыми файлами
void write_to_text_file(const std::string& filename, const std::string& data);
std::string read_from_text_file(const std::string& filename);
void append_to_text_file(const std::string& filename, const std::string& data);

// Функции для работы с бинарными файлами
void write_to_binary_file(const std::string& filename, const std::vector<char>& data);
std::vector<char> read_from_binary_file(const std::string& filename);
void append_to_binary_file(const std::string& filename, const std::vector<char>& data);

// Вспомогательные функции
bool file_exists(const std::string& filename);
size_t get_file_size(const std::string& filename);
void validate_text_file(const std::string& filename);
void validate_binary_file(const std::string& filename);// Ввод и валидация количества страниц

#endif //INC_5_LAB_FUNC_WITH_EXC_H