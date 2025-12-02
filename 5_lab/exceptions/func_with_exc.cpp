#include <regex>                           // Для работы с регулярными выражениями
#include <chrono>                          // Для работы со временем (хотя не используется)
#include <filesystem>
#include "func_with_exc.h"                 // Заголовочный файл с исключениями


std::string input_author(std::istream& is)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw author_validation_exception("Имя автора не может быть пустым", AUTHOR_EMPTY);

    if (!(input[0] >= 'A' && input[0] <= 'Z'))
        throw author_validation_exception("Первая буква имени автора должна быть заглавной", AUTHOR_CAPITALIZATION);

    for (size_t i = 1; i < input.length(); ++i)
    {
        if (!(input[i] >= 'a' && input[i] <= 'z'))
            throw author_validation_exception("Все буквы после первой должны быть строчными", AUTHOR_INVALID_CHARS);
    }

    return input;
}

int input_num(std::istream& is, int min, int max)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw number_validation_exception("Поле не может быть пустым", NUMBER_EMPTY);

    if (!std::regex_match(input, std::regex("^[0-9]+$")))
        throw number_validation_exception("Поле должно содержать только цифры", NUMBER_INVALID);

    int number = std::stoi(input);

    if (number > max || number < min)
        throw number_validation_exception("Значение должно быть в диапазоне от " +
                                          std::to_string(min) + " до " +
                                          std::to_string(max), NUMBER_OUT_OF_RANGE);

    return number;
}


std::string input_title(std::istream& is)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw title_validation_exception("Название не может быть пустым", TITLE_EMPTY);

    if(!std::regex_match(input, std::regex("^[A-Za-z0-9]+(?:[\\s.,!?][A-Za-z0-9]+)*$")))
        throw title_validation_exception("Название должно содержать только латинские буквы, цифры и знаки . , ! ?", TITLE_INVALID_CHARS);


    return input;
}

std::string input_single_word(std::istream& is, const std::string& field_name)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);

    if (input.find(' ') != std::string::npos)
        throw word_validation_exception(field_name + " должен быть одним словом", WORD_INVALID_CHARS);

    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+$")))
        throw word_validation_exception(field_name + " должен содержать только латинские буквы и цифры", WORD_INVALID_CHARS);

    return input;
}

std::string input_word_with_hyphen(std::istream& is, const std::string& field_name)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);

    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+(-[A-Za-z0-9]+)*$")))
        throw word_validation_exception("Некорректный формат " + field_name + " (разрешены только латинские буквы, цифры и дефисы)", WORD_HYPHEN_POSITION);

    return input;
}

std::string to_lower(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

 void validate_extension(const std::string& filename,
                               const std::string& expected_ext,
                               const std::string& file_type)
{
    if (filename.find('.') == std::string::npos)
        throw file_format_exception(
                "Файл '" + filename + "' должен иметь расширение " + expected_ext +
                " для " + file_type + " файлов",
                FILE_EXTENSION_ERROR
        );

    std::string ext = filename.substr(filename.find_last_of('.'));
    if (to_lower(ext) != to_lower(expected_ext))
        throw file_format_exception(
                "Неверное расширение файла '" + filename + "'. Ожидается " +
                expected_ext + " для " + file_type + " файлов, но найдено " + ext,
                FILE_EXTENSION_ERROR
        );
}

void validate_text_file_extension(const std::string& filename)
{
    validate_extension(filename, ".txt", "текстовых");
}

void validate_binary_file_extension(const std::string& filename)
{
    validate_extension(filename, ".bin", "бинарных");
}

void safe_open_for_read(std::ifstream& stream, const std::string& filename)
{
    stream.open(filename, std::ios::in);
    if (!stream.is_open())
        throw file_open_exception("Не удалось открыть файл для чтения: " + filename, FILE_OPEN_ERROR);
}

void safe_open_for_write(std::ofstream& stream, const std::string& filename)
{
    stream.open(filename, std::ios::out);
    if (!stream.is_open())
        throw file_open_exception("Не удалось открыть файл для записи: " + filename, FILE_OPEN_ERROR);
}

void safe_open_for_binary_read(std::fstream& stream, const std::string& filename)
{
    stream.open(filename, std::ios::binary | std::ios::in);
    if (!stream.is_open())
        throw file_open_exception("Не удалось открыть бинарный файл для чтения: " + filename, FILE_OPEN_ERROR);
}

void safe_open_for_binary_write(std::fstream& stream, const std::string& filename)
{
    stream.open(filename, std::ios::binary | std::ios::out);
    if (!stream.is_open())
        throw file_open_exception("Не удалось открыть бинарный файл для записи: " + filename, FILE_OPEN_ERROR);
}

void check_file_not_empty(std::fstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт: " + filename, FILE_OPEN_ERROR);

    std::streampos current_pos = stream.tellg();
    stream.seekg(0, std::ios::end);
    bool empty = (stream.tellg() == 0);
    stream.seekg(current_pos);

    if (empty)
        throw file_access_exception("Файл пуст: " + filename, FILE_ACCESS_ERROR);
}

void check_file_not_empty(std::ifstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт: " + filename, FILE_OPEN_ERROR);

    std::streampos current_pos = stream.tellg();
    stream.seekg(0, std::ios::end);
    bool empty = (stream.tellg() == 0);
    stream.seekg(current_pos);

    if (empty)
        throw file_access_exception("Файл пуст: " + filename, FILE_ACCESS_ERROR);
}

void check_file_opened_for_read(std::fstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт для чтения: " + filename, FILE_OPEN_ERROR);
}

void check_file_opened_for_write(std::fstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт для записи: " + filename, FILE_OPEN_ERROR);
}

void check_file_opened_for_read(std::ifstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт для чтения: " + filename, FILE_OPEN_ERROR);
}

void check_file_opened_for_write(std::ofstream& stream, const std::string& filename)
{
    if (!stream.is_open())
        throw file_access_exception("Файл не открыт для записи: " + filename, FILE_OPEN_ERROR);
}

void check_not_end_of_file(std::fstream& stream, const std::string& filename)
{
    if (stream.peek() == EOF)
        throw std::runtime_error("Конец файла достигнут: " + filename);
}

void check_not_end_of_file(std::ifstream& stream, const std::string& filename)
{
    if (stream.peek() == EOF)
        throw std::runtime_error("Конец файла достигнут: " + filename);
}

void check_write_success(std::fstream& stream, const std::string& filename, const std::string& operation)
{
    if (stream.fail())
        throw file_access_exception("Ошибка записи " + operation + " в файл: " + filename, FILE_ACCESS_ERROR);
}

void check_write_success(std::ofstream& stream, const std::string& filename, const std::string& operation)
{
    if (stream.fail())
        throw file_access_exception("Ошибка записи " + operation + " в файл: " + filename, FILE_ACCESS_ERROR);
}

void check_read_success(std::fstream& stream, const std::string& filename, const std::string& operation)
{
    if (stream.fail())
    {
        if (stream.eof())
            throw std::runtime_error("Конец файла достигнут при чтении " + operation + ": " + filename);
        throw file_access_exception("Ошибка чтения " + operation + " из файла: " + filename, FILE_ACCESS_ERROR);
    }
}

void check_read_success(std::ifstream& stream, const std::string& filename, const std::string& operation)
{
    if (stream.fail())
    {
        if (stream.eof())
            throw std::runtime_error("Конец файла достигнут при чтении " + operation + ": " + filename);
        throw file_access_exception("Ошибка чтения " + operation + " из файла: " + filename, FILE_ACCESS_ERROR);
    }
}

void safe_clear_file(const std::string& filename)
{
    std::ofstream clear_stream(filename, std::ios::binary | std::ios::trunc);
    if (!clear_stream.is_open())
        throw file_access_exception("Не удалось очистить файл: " + filename, FILE_ACCESS_ERROR);
    clear_stream.close();
}