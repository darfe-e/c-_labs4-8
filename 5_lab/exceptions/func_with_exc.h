#ifndef INC_5_LAB_FUNC_WITH_EXC_H
#define INC_5_LAB_FUNC_WITH_EXC_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "headers/input_exceptions/author_validation_exception.h"
#include "headers/input_exceptions/title_validation_exception.h"
#include "headers/input_exceptions/word_validation_exception.h"
#include "headers/input_exceptions/number_validation_exception.h"

#include "headers/file_exceptions/file_access_exception .h"
#include "headers/file_exceptions/file_exception .h"
#include "headers/file_exceptions/file_format_exception .h"
#include "headers/file_exceptions/file_open_exception .h"

// Коды ошибок
enum ErrorCodes
{
    AUTHOR_EMPTY = 1001,
    AUTHOR_INVALID_CHARS = 1002,
    AUTHOR_CAPITALIZATION = 1003,

    TITLE_EMPTY = 2001,
    TITLE_INVALID_CHARS = 2002,

    WORD_EMPTY = 3001,
    WORD_INVALID_CHARS = 3002,
    WORD_HYPHEN_POSITION = 3003,

    NUMBER_EMPTY = 4001,
    NUMBER_INVALID = 4002,
    NUMBER_OUT_OF_RANGE = 4003,

    FILE_OPEN_ERROR = 6001,
    FILE_FORMAT_ERROR = 6004,
    FILE_ACCESS_ERROR = 6005,
    FILE_EXTENSION_ERROR = 6007  // НОВЫЙ КОД ОШИБКИ ДЛЯ РАСШИРЕНИЙ
};

// Функции валидации строк
std::string input_author(std::istream& is);
std::string input_title(std::istream& is);
std::string input_single_word(std::istream& is, const std::string& field_name);
std::string input_word_with_hyphen(std::istream& is, const std::string& field_name);

// Функции валидации чисел
int input_num(std::istream& is, int min, int max);

std::string to_lower(const std::string& str);
void validate_extension(const std::string& filename,
                        const std::string& expected_ext,
                        const std::string& file_type);
void validate_text_file_extension(const std::string& filename);
void validate_binary_file_extension(const std::string& filename);
void safe_open_for_read(std::ifstream& stream, const std::string& filename);
void safe_open_for_write(std::ofstream& stream, const std::string& filename);
void safe_open_for_binary_read(std::fstream& stream, const std::string& filename);
void safe_open_for_binary_write(std::fstream& stream, const std::string& filename);
bool is_file_empty(std::fstream& stream);
void check_file_not_empty(std::fstream& stream, const std::string& filename);
void check_file_not_empty(std::ifstream& stream, const std::string& filename);
void check_file_opened_for_read(std::fstream& stream, const std::string& filename);
void check_file_opened_for_write(std::fstream& stream, const std::string& filename);
void check_file_opened_for_read(std::ifstream& stream, const std::string& filename);
void check_file_opened_for_write(std::ofstream& stream, const std::string& filename);
void check_not_end_of_file(std::fstream& stream, const std::string& filename);
void check_not_end_of_file(std::ifstream& stream, const std::string& filename);
void check_write_success(std::fstream& stream, const std::string& filename, const std::string& operation);
void check_write_success(std::ofstream& stream, const std::string& filename, const std::string& operation);
void check_read_success(std::fstream& stream, const std::string& filename, const std::string& operation);
void check_read_success(std::ifstream& stream, const std::string& filename, const std::string& operation);
void safe_clear_file(const std::string& filename);

#endif //INC_5_LAB_FUNC_WITH_EXC_H