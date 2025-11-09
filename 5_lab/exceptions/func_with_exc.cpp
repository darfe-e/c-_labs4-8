#include <regex>
#include <chrono>
#include "func_with_exc.h"

std::string input_author(std::istream& is)
{
    std::string input;
    std::getline(is, input);                                                                             // Чтение строки из потока

    if (input.empty())
        throw author_validation_exception("Автор не может быть пустым", AUTHOR_EMPTY);                  // Проверка на пустую строку

    if (input.length() > 10)
        throw author_validation_exception("Имя автора не должно превышать 10 символов", AUTHOR_TOO_LONG); // Проверка длины

    // Проверка на английские символы и первую заглавную букву
    if (!std::regex_match(input, std::regex("^[A-Z][a-z]*$")))
    {
        if (!std::isupper(input[0]))
            throw author_validation_exception("Первая буква имени автора должна быть заглавной", AUTHOR_CAPITALIZATION); // Проверка первой буквы
        if (!std::regex_match(input, std::regex("^[A-Za-z]*$")))
            throw author_validation_exception("Имя автора должно содержать только английские буквы", AUTHOR_INVALID_CHARS); // Проверка символов
        throw author_validation_exception("Некорректный формат имени автора", AUTHOR_INVALID_CHARS);     // Общая ошибка формата
    }

    return input;                                                                                        // Возврат валидного значения
}

std::string input_title(std::istream& is)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw title_validation_exception("Название не может быть пустым", TITLE_EMPTY);

    size_t start = input.find_first_not_of(" \t");
    size_t end = input.find_last_not_of(" \t");
    if (start == std::string::npos)
        throw title_validation_exception("Название не может состоять только из пробелов", TITLE_EMPTY);
    input = input.substr(start, end - start + 1);

    bool lastWasPunctuation = false;
    bool inWord = false;
    bool currentWordHasLetters = false;
    bool currentWordHasDigits = false;
    bool firstWordChecked = false;

    for (size_t i = 0; i < input.length(); ++i)
    {
        char c = input[i];
        unsigned char uc = static_cast<unsigned char>(c);

        if (std::isspace(uc))
        {
            if (lastWasPunctuation)
                lastWasPunctuation = false;
            inWord = false;
            currentWordHasLetters = false;
            currentWordHasDigits = false;
            continue;
        }
        else if (std::isalpha(uc))
        {
            if (lastWasPunctuation)
                throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);

            if (!inWord)
            {
                inWord = true;
                currentWordHasLetters = true;
                currentWordHasDigits = false;

                // Проверяем только первую букву первого слова
                if (!firstWordChecked)
                {
                    if (!std::isupper(uc))
                        throw title_validation_exception("Первая буква названия должна быть заглавной", TITLE_CAPITALIZATION);
                    firstWordChecked = true;
                }
            }
            else
            {
                // Проверяем, что в середине слова нет заглавных букв
                if (std::isupper(uc))
                    throw title_validation_exception("В середине слова не может быть заглавных букв", TITLE_INVALID_CHARS);

                if (currentWordHasDigits)
                    throw title_validation_exception("Слово не может содержать одновременно буквы и цифры", TITLE_INVALID_CHARS);
            }
            continue;
        }
        else if (std::isdigit(uc))
        {
            if (lastWasPunctuation)
                throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);

            if (!inWord)
            {
                inWord = true;
                currentWordHasDigits = true;
                currentWordHasLetters = false;
                firstWordChecked = true; // Числовое слово считается как первое слово
            }
            else
            {
                if (currentWordHasLetters)
                    throw title_validation_exception("Слово не может содержать одновременно буквы и цифры", TITLE_INVALID_CHARS);
            }
            continue;
        }
        else if (std::ispunct(uc))
        {
            if (c != '.' && c != '!' && c != '?' && c != ',')
                throw title_validation_exception("Разрешенные знаки препинания: . ! ? ,", TITLE_INVALID_CHARS);

            if (i == input.length() - 1)
                break;
            else
            {
                if (i + 1 >= input.length() || !std::isspace(static_cast<unsigned char>(input[i + 1])))
                    throw title_validation_exception("После знака препинания должен быть пробел", TITLE_INVALID_CHARS);
                lastWasPunctuation = true;
                inWord = false;
                currentWordHasLetters = false;
                currentWordHasDigits = false;
            }
            continue;
        }
        else
            throw title_validation_exception("Название содержит недопустимые символы", TITLE_INVALID_CHARS);
    }

    return input;
}

std::string input_single_word(std::istream& is, const std::string& field_name)
{
    std::string input;
    std::getline(is, input);                                                                             // Чтение строки из потока

    if (input.empty())
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);              // Проверка на пустую строку

    // Проверка на одно слово (без пробелов)
    if (input.find(' ') != std::string::npos)
        throw word_validation_exception(field_name + " должен быть одним словом", WORD_INVALID_CHARS);   // Проверка на пробелы

    // Проверка на буквенно-цифровые символы
    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+$")))
        throw word_validation_exception(field_name + " должен содержать только буквы и цифры", WORD_INVALID_CHARS); // Проверка символов

    return input;                                                                                        // Возврат валидного значения
}

std::string input_word_with_hyphen(std::istream& is, const std::string& field_name)
{
    std::string input;
    std::getline(is, input);                                                                             // Чтение строки из потока

    if (input.empty())
        throw word_validation_exception(field_name + " не может быть пустым", WORD_EMPTY);              // Проверка на пустую строку

    // Проверка на одно слово с возможным дефисом в середине
    if (!std::regex_match(input, std::regex("^[A-Za-z0-9]+(-[A-Za-z0-9]+)*$")))
        throw word_validation_exception("Некорректный формат " + field_name, WORD_HYPHEN_POSITION);     // Проверка формата с дефисом

    return input;                                                                                        // Возврат валидного значения
}

int input_year(std::istream& is)
{
    std::string input;
    std::getline(is, input);

    if (input.empty())
        throw year_validation_exception("Год не может быть пустым", YEAR_EMPTY);

    if (!std::regex_match(input, std::regex("^[0-9]+$")))
        throw year_validation_exception("Год должен содержать только цифры", YEAR_INVALID);

    try
    {
        int year = std::stoi(input);

        // Получаем текущий год без chrono
        std::time_t t = std::time(nullptr);          // Текущее время в секундах с эпохи
        std::tm* now = std::localtime(&t);           // Преобразуем в структуру tm
        int current_year = now->tm_year + 1900;      // tm_year отсчитывается с 1900 года

        if (year < 1500 || year > current_year + 1)
            throw year_validation_exception("Год должен быть в диапазоне от 1500 до " +
                                            std::to_string(current_year + 1), YEAR_OUT_OF_RANGE);

        return year;
    }
    catch (const std::exception& e)
    {
        throw year_validation_exception("Некорректный формат года", YEAR_INVALID);
    }
}

int input_circulation(std::istream& is)
{
    std::string input;
    std::getline(is, input);                                                                             // Чтение строки из потока

    if (input.empty())
        throw number_validation_exception("Тираж не может быть пустым", NUMBER_EMPTY);                  // Проверка на пустую строку

    if (!std::regex_match(input, std::regex("^[0-9]+$")))
        throw number_validation_exception("Тираж должен содержать только цифры", NUMBER_INVALID);       // Проверка цифрового формата

    if (input.length() > 9)
        throw number_validation_exception("Тираж не должен превышать 9 цифр", NUMBER_TOO_LONG);         // Проверка длины числа

    try
    {
        return std::stoi(input);                                                                         // Преобразование строки в число
    }
    catch (const std::exception& e)
    {
        throw number_validation_exception("Некорректный формат тиража", NUMBER_INVALID);                // Обработка ошибки преобразования
    }
}

int input_pages(std::istream& is)
{
    std::string input;
    std::getline(is, input);                                                                             // Чтение строки из потока

    if (input.empty())
        throw number_validation_exception("Количество страниц не может быть пустым", NUMBER_EMPTY);     // Проверка на пустую строку

    if (!std::regex_match(input, std::regex("^[0-9]+$")))
        throw number_validation_exception("Количество страниц должно содержать только цифры", NUMBER_INVALID); // Проверка цифрового формата

    if (input.length() > 9)
        throw number_validation_exception("Количество страниц не должно превышать 9 цифр", NUMBER_TOO_LONG); // Проверка длины числа

    try
    {
        return std::stoi(input);                                                                         // Преобразование строки в число
    }
    catch (const std::exception& e)
    {
        throw number_validation_exception("Некорректный формат количества страниц", NUMBER_INVALID);    // Обработка ошибки преобразования
    }
}