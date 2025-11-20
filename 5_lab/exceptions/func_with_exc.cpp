#include <regex>                           // Для работы с регулярными выражениями
#include <chrono>                          // Для работы со временем (хотя не используется)
#include <filesystem>
#include "func_with_exc.h"                 // Заголовочный файл с исключениями


std::string input_author(std::istream& is)
{
    std::string input;                     // Переменная для хранения ввода
    std::getline(is, input);         // Чтение всей строки из входного потока

    if (input.empty())                     // Проверка на пустую строку
        throw author_validation_exception("Автор не может быть пустым", AUTHOR_EMPTY);

    if (input.length() > 10)               // Проверка максимальной длины (10 символов)
        throw author_validation_exception("Имя автора не должно превышать 10 символов", AUTHOR_TOO_LONG);

    // Проверка на наличие только латинских букв
    if (!std::regex_match(input, std::regex("^[A-Za-z]+$")))
        throw author_validation_exception("Имя автора должно содержать только латинские буквы", AUTHOR_INVALID_CHARS);

    // Проверка формата: Заглавная + строчные
    if (!(input[0] >= 'A' && input[0] <= 'Z')) // Проверка первой буквы на заглавную
        throw author_validation_exception("Первая буква имени автора должна быть заглавной", AUTHOR_CAPITALIZATION);

    // Проверка что остальные буквы строчные
    for (size_t i = 1; i < input.length(); ++i)
    {
        if (!(input[i] >= 'a' && input[i] <= 'z'))
            throw author_validation_exception("Все буквы после первой должны быть строчными", AUTHOR_INVALID_CHARS);
    }

    return input;                          // Возврат валидного значения
}

std::string input_title(std::istream& is)
{
    std::string input;                     // Переменная для хранения ввода
    std::getline(is, input);         // Чтение всей строки из входного потока

    if (input.empty())                     // Проверка на пустую строку
        throw title_validation_exception("Название не может быть пустым", TITLE_EMPTY);

    size_t start = input.find_first_not_of(" \t"); // Поиск первого непробельного символа
    size_t end = input.find_last_not_of(" \t");    // Поиск последнего непробельного символа
    if (start == std::string::npos)                    // Если строка состоит только из пробелов
        throw title_validation_exception("Название не может состоять только из пробелов", TITLE_EMPTY);
    input = input.substr(start, end - start + 1); // Обрезка пробелов по краям

    // Проверка на наличие только латинских букв, цифр и разрешенных знаков препинания
    if (!std::regex_match(input, std::regex("^[A-Za-z0-9\\s.,!?]+$")))
        throw title_validation_exception("Название должно содержать только латинские буквы, цифры и знаки . , ! ?", TITLE_INVALID_CHARS);

    bool lastWasPunctuation = false;       // Флаг: предыдущий символ был знаком препинания
    bool inWord = false;                   // Флаг: находимся внутри слова
    bool currentWordHasLetters = false;    // Флаг: текущее слово содержит буквы
    bool currentWordHasDigits = false;     // Флаг: текущее слово содержит цифры
    bool firstWordChecked = false;         // Флаг: первое слово проверено на заглавную букву

    for (size_t i = 0; i < input.length(); ++i) // Посимвольный обход строки
    {
        char c = input[i];                      // Текущий символ

        // Безопасная проверка на латинские символы
        bool isLatinUpper = (c >= 'A' && c <= 'Z');
        bool isLatinLower = (c >= 'a' && c <= 'z');
        bool isDigit = (c >= '0' && c <= '9');
        bool isSpace = (c == ' ' || c == '\t');
        bool isPunctuation = (c == '.' || c == '!' || c == '?' || c == ',');

        if (isSpace)                // Если символ - пробел
        {
            if (lastWasPunctuation)        // Если перед пробелом был знак препинания
                lastWasPunctuation = false;// Сбрасываем флаг знака препинания
            inWord = false;                // Выходим из слова
            currentWordHasLetters = false; // Сбрасываем флаг букв
            currentWordHasDigits = false;  // Сбрасываем флаг цифр
            continue;                      // Переход к следующему символу
        }
        else if (isLatinUpper || isLatinLower)      // Если символ - латинская буква
        {
            if (lastWasPunctuation)        // Проверка: после знака препинания должен быть пробел
                throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);

            if (!inWord)                      // Если начинается новое слово
            {
                inWord = true;                // Входим в слово
                currentWordHasLetters = true; // Устанавливаем флаг букв
                currentWordHasDigits = false; // Сбрасываем флаг цифр

                if (!firstWordChecked)        // Если первое слово еще не проверялось
                {
                    if (!isLatinUpper) // Проверка первой буквы первого слова на заглавную
                        throw title_validation_exception("Первая буква названия должна быть заглавной", TITLE_CAPITALIZATION);
                    firstWordChecked = true;  // Отмечаем, что первое слово проверено
                }
            }
            else                             // Если продолжаем слово
            {
                if (isLatinUpper)     // Проверка: в середине слова не должно быть заглавных
                    throw title_validation_exception("В середине слова не может быть заглавных букв", TITLE_INVALID_CHARS);

                if (currentWordHasDigits)    // Проверка: слово не может содержать и буквы, и цифры
                    throw title_validation_exception("Слово не может содержать одновременно буквы и цифры", TITLE_INVALID_CHARS);
            }
            continue;                        // Переход к следующему символу
        }
        else if (isDigit)        // Если символ - цифра
        {
            if (lastWasPunctuation)          // Проверка: после знака препинания должен быть пробел
                throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);

            if (!inWord)                       // Если начинается новое слово
            {
                inWord = true;                 // Входим в слово
                currentWordHasDigits = true;   // Устанавливаем флаг цифр
                currentWordHasLetters = false; // Сбрасываем флаг букв
                firstWordChecked = true;       // Числовое слово считается первым (пропускаем проверку заглавной)
            }
            else                               // Если продолжаем слово
            {
                if (currentWordHasLetters)     // Проверка: слово не может содержать и буквы, и цифры
                    throw title_validation_exception("Слово не может содержать одновременно буквы и цифры", TITLE_INVALID_CHARS);
            }
            continue;                       // Переход к следующему символу
        }
        else if (isPunctuation)       // Если символ - знак препинания
        {
            if (i == input.length() - 1)  // Если знак препинания в конце строки
                break;                    // Завершаем проверку
            else                          // Если знак препинания в середине строки
            {
                if (i + 1 >= input.length() || !(input[i + 1] == ' ' || input[i + 1] == '\t')) // Проверка пробела после знака
                    throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);
                lastWasPunctuation = true;     // Устанавливаем флаг знака препинания
                inWord = false;                // Выходим из слова
                currentWordHasLetters = false; // Сбрасываем флаг букв
                currentWordHasDigits = false;  // Сбрасываем флаг цифр
            }
            continue;                     // Переход к следующему символу
        }
    }

    return input;                         // Возврат валидного названия
}

std::string input_single_word(std::istream& is, const std::string& field_name)
{
    std::string input;                    // Переменная для хранения ввода
    std::getline(is, input);        // Чтение всей строки из входного потока

    if (input.empty())                    // Проверка на пустую строку
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);

    if (input.find(' ') != std::string::npos) // Проверка на наличие пробелов (должно быть одно слово)
        throw word_validation_exception(field_name + " должен быть одним словом", WORD_INVALID_CHARS);

    // Проверка на латинские буквы и цифры
    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+$")))
        throw word_validation_exception(field_name + " должен содержать только латинские буквы и цифры", WORD_INVALID_CHARS);

    return input;                         // Возврат валидного значения
}

std::string input_word_with_hyphen(std::istream& is, const std::string& field_name)
{
    std::string input;                    // Переменная для хранения ввода
    std::getline(is, input);        // Чтение всей строки из входного потока

    if (input.empty())                    // Проверка на пустую строку
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);

    // Проверка формата с дефисами (только латинские буквы, цифры и дефисы)
    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+(-[A-Za-z0-9]+)*$")))
        throw word_validation_exception("Некорректный формат " + field_name + " (разрешены только латинские буквы, цифры и дефисы)", WORD_HYPHEN_POSITION);

    return input;                         // Возврат валидного значения
}

int input_year(std::istream& is)
{
    std::string input;                    // Переменная для хранения ввода
    std::getline(is, input);        // Чтение всей строки из входного потока

    if (input.empty())                    // Проверка на пустую строку
        throw year_validation_exception("Год не может быть пустым", YEAR_EMPTY);

    if (!std::regex_match(input, std::regex("^[0-9]+$"))) // Проверка, что строка содержит только цифры
        throw year_validation_exception("Год должен содержать только цифры", YEAR_INVALID);

    try
    {
        int year = std::stoi(input);          // Преобразование строки в число

        std::time_t t = std::time(nullptr); // Получение текущего времени
        std::tm* now = std::localtime(&t);  // Преобразование в локальное время
        int current_year = now->tm_year + 1900;   // Вычисление текущего года (tm_year с 1900)

        if (year < 1500 || year > current_year + 1) // Проверка диапазона года
            throw year_validation_exception("Год должен быть в диапазоне от 1500 до " +
                                            std::to_string(current_year + 1), YEAR_OUT_OF_RANGE);

        return year;                      // Возврат валидного года
    }
    catch (const std::exception& e)       // Обработка ошибок преобразования
    {
        throw year_validation_exception("Некорректный формат года", YEAR_INVALID);
    }
}

int input_circulation(std::istream& is)
{
    std::string input;                    // Переменная для хранения ввода
    std::getline(is, input);        // Чтение всей строки из входного потока

    if (input.empty())                    // Проверка на пустую строку
        throw number_validation_exception("Тираж не может быть пустым", NUMBER_EMPTY);

    if (!std::regex_match(input, std::regex("^[0-9]+$"))) // Проверка, что строка содержит только цифры
        throw number_validation_exception("Тираж должен содержать только цифры", NUMBER_INVALID);

    if (input.length() > 9)               // Проверка максимальной длины (9 цифр)
        throw number_validation_exception("Тираж не должен превышать 9 цифр", NUMBER_TOO_LONG);

    try
    {
        return std::stoi(input);      // Преобразование строки в число и возврат
    }
    catch (const std::exception& e)       // Обработка ошибок преобразования
    {
        throw number_validation_exception("Некорректный формат тиража", NUMBER_INVALID);
    }
}

int input_pages(std::istream& is)
{
    std::string input;                    // Переменная для хранения ввода
    std::getline(is, input);        // Чтение всей строки из входного потока

    if (input.empty())                    // Проверка на пустую строку
        throw number_validation_exception("Количество страниц не может быть пустым", NUMBER_EMPTY);

    if (!std::regex_match(input, std::regex("^[0-9]+$"))) // Проверка, что строка содержит только цифры
        throw number_validation_exception("Количество страниц должно содержать только цифры", NUMBER_INVALID);

    if (input.length() > 9)               // Проверка максимальной длины (9 цифр)
        throw number_validation_exception("Количество страниц не должно превышать 9 цифр", NUMBER_TOO_LONG);

    try
    {
        return std::stoi(input);      // Преобразование строки в число и возврат
    }
    catch (const std::exception& e)       // Обработка ошибок преобразования
    {
        throw number_validation_exception("Некорректный формат количества страниц", NUMBER_INVALID);
    }
}


// Добавляем в существующий файл func_with_exc.cpp

// Запись в текстовый файл
void write_to_text_file(const std::string& filename, const std::string& data)
{
    if (filename.empty())
    {
        throw file_exception("Имя файла не может быть пустым", FILE_ACCESS_ERROR);
    }

    // Проверка расширения файла
    if (filename.size() < 5 || filename.substr(filename.size() - 4) != ".txt")
    {
        throw file_format_exception("Файл должен иметь расширение .txt", FILE_FORMAT_ERROR);
    }

    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    if (!file.is_open())
    {
        throw file_open_exception("Не удалось открыть текстовый файл для записи: " + filename, FILE_OPEN_ERROR);
    }

    try
    {
        file << data;
        if (file.fail())
        {
            throw file_write_exception("Ошибка записи в текстовый файл: " + filename, FILE_WRITE_ERROR);
        }

        // Проверяем, что данные действительно записались
        file.flush();
        if (file.fail())
        {
            throw file_write_exception("Ошибка сохранения данных в файл: " + filename, FILE_WRITE_ERROR);
        }
    }
    catch (const std::exception& e)
    {
        file.close();
        throw file_write_exception("Исключение при записи в текстовый файл: " + std::string(e.what()), FILE_WRITE_ERROR);
    }

    file.close();
}

// Чтение из текстового файла
std::string read_from_text_file(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        throw file_open_exception("Текстовый файл не существует: " + filename, FILE_OPEN_ERROR);
    }

    // Проверка расширения файла
    if (filename.size() < 5 || filename.substr(filename.size() - 4) != ".txt")
    {
        throw file_format_exception("Файл должен иметь расширение .txt", FILE_FORMAT_ERROR);
    }

    if (!std::filesystem::is_regular_file(filename))
    {
        throw file_access_exception("Не является обычным файлом: " + filename, FILE_ACCESS_ERROR);
    }

    // Проверка размера файла
    auto file_size = std::filesystem::file_size(filename);
    if (file_size == 0)
    {
        throw file_read_exception("Текстовый файл пустой: " + filename, FILE_READ_ERROR);
    }

    if (file_size > 10 * 1024 * 1024) // 10 MB limit
    {
        throw file_access_exception("Текстовый файл слишком большой: " + filename, FILE_ACCESS_ERROR);
    }

    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        throw file_open_exception("Не удалось открыть текстовый файл для чтения: " + filename, FILE_OPEN_ERROR);
    }

    std::stringstream buffer;
    try
    {
        buffer << file.rdbuf();
        if (file.fail() && !file.eof())
        {
            throw file_read_exception("Ошибка чтения из текстового файла: " + filename, FILE_READ_ERROR);
        }
    }
    catch (const std::exception& e)
    {
        file.close();
        throw file_read_exception("Исключение при чтении текстового файла: " + std::string(e.what()), FILE_READ_ERROR);
    }

    file.close();

    std::string content = buffer.str();
    if (content.empty())
    {
        throw file_read_exception("Содержимое файла пустое после чтения: " + filename, FILE_READ_ERROR);
    }

    return content;
}

// Запись в бинарный файл
void write_to_binary_file(const std::string& filename, const std::vector<char>& data)
{
    if (filename.empty())
    {
        throw file_exception("Имя файла не может быть пустым", FILE_ACCESS_ERROR);
    }

    // Проверка расширения файла
    if (filename.size() < 5 || filename.substr(filename.size() - 4) != ".bin")
    {
        throw file_format_exception("Бинарный файл должен иметь расширение .bin", FILE_FORMAT_ERROR);
    }

    if (data.empty())
    {
        throw file_write_exception("Данные для записи не могут быть пустыми", FILE_WRITE_ERROR);
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!file.is_open())
    {
        throw file_open_exception("Не удалось открыть бинарный файл для записи: " + filename, FILE_OPEN_ERROR);
    }

    try
    {
        file.write(data.data(), data.size());
        if (file.fail())
        {
            throw file_write_exception("Ошибка записи в бинарный файл: " + filename, FILE_WRITE_ERROR);
        }

        // Проверяем, что записалось правильное количество байт
        if (file.tellp() != static_cast<std::streampos>(data.size()))
        {
            throw file_write_exception("Записано неверное количество данных в бинарный файл: " + filename, FILE_WRITE_ERROR);
        }
    }
    catch (const std::exception& e)
    {
        file.close();
        throw file_write_exception("Исключение при записи в бинарный файл: " + std::string(e.what()), FILE_WRITE_ERROR);
    }

    file.close();
}

// Чтение из бинарного файла
std::vector<char> read_from_binary_file(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        throw file_open_exception("Бинарный файл не существует: " + filename, FILE_OPEN_ERROR);
    }

    // Проверка расширения файла
    if (filename.size() < 5 || filename.substr(filename.size() - 4) != ".bin")
    {
        throw file_format_exception("Файл должен иметь расширение .bin", FILE_FORMAT_ERROR);
    }

    if (!std::filesystem::is_regular_file(filename))
    {
        throw file_access_exception("Не является обычным файлом: " + filename, FILE_ACCESS_ERROR);
    }

    // Проверка размера файла
    auto file_size = std::filesystem::file_size(filename);
    if (file_size == 0)
    {
        throw file_read_exception("Бинарный файл пустой: " + filename, FILE_READ_ERROR);
    }

    if (file_size > 50 * 1024 * 1024) // 50 MB limit для бинарных файлов
    {
        throw file_access_exception("Бинарный файл слишком большой: " + filename, FILE_ACCESS_ERROR);
    }

    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        throw file_open_exception("Не удалось открыть бинарный файл для чтения: " + filename, FILE_OPEN_ERROR);
    }

    std::vector<char> data(file_size);
    try
    {
        file.read(data.data(), file_size);
        if (file.fail() && !file.eof())
        {
            throw file_read_exception("Ошибка чтения из бинарного файла: " + filename, FILE_READ_ERROR);
        }

        // Проверяем, что прочитали правильное количество байт
        std::streamsize bytes_read = file.gcount();
        if (bytes_read != static_cast<std::streamsize>(file_size))
        {
            throw file_read_exception("Прочитано неверное количество данных из бинарного файла: " + filename, FILE_READ_ERROR);
        }
    }
    catch (const std::exception& e)
    {
        file.close();
        throw file_read_exception("Исключение при чтении бинарного файла: " + std::string(e.what()), FILE_READ_ERROR);
    }

    file.close();
    return data;
}

// Вспомогательные функции
bool file_exists(const std::string& filename)
{
    return std::filesystem::exists(filename);
}

size_t get_file_size(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        throw file_open_exception("Файл не существует: " + filename, FILE_OPEN_ERROR);
    }

    return std::filesystem::file_size(filename);
}