#include "library_manager.h"
#include <windows.h>
#include <filesystem>

template<class T>
LibraryManager<T>::LibraryManager(const std::string& name) : className(name)
{
    auto comparator = _choose_comparator();
    tree = binaryTree<T>(comparator);
}

template<class T>
void LibraryManager<T>::_displayMenu() const
{
    std::cout << "\033[36m" << "\n\nНажмите Enter для продолжения..." << "\033[0m";
    std::cin.get();
    system("cls");
    std::cout  << "\n=== РАБОТА С " << className << " ==="
              << "\n1. Добавить карточку"
              << "\n2. Найти карточку по нескольким полям"
              << "\n3. Вывести отсортированное по возрастанию дерево"
              << "\n4. Вывести отсортированное по убыванию дерево"
              << "\n5. Удалить узел с заданной характеристикой"
              << "\n6. Вывести дерево (pre-order)"
              << "\n7. Поиск по условию (find_if)"
              << "\n8. Операции с файлами"
              << "\n9. Вернуться в главное меню"
               << "\n\nВаш выбор: ";
}

template<class T>
int LibraryManager<T>::_getUserChoice()
{
    int choice;
    std::cin >> choice;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::runtime_error("Неверный ввод. Пожалуйста, введите число.");
    }
    std::cin.ignore(10000, '\n'); // Очищаем буфер после ввода числа
    return choice;
}

template<class T>
void LibraryManager<T>::run()
{
    int choice;

    do
    {
        _displayMenu();
        try
        {
            choice = _getUserChoice();
            _processChoice(choice);
        }
        catch (const std::exception& e)
        {
            std::cout  << e.what()  << std::endl;
        }

    } while (choice != 9);
}

template<class T>
void LibraryManager<T>::_processChoice(int choice)
{
    switch(choice)
    {
        case 1: // Добавить карточку
        {
            T card;
            std::cout  << "\n=== ДОБАВЛЕНИЕ КАРТОЧКИ ==="  << std::endl;

            try
            {
                std::cin >> card;
                tree.push(card);
                std::cout << " Карточка успешно добавлена!" << std::endl;
            }
            catch (const author_validation_exception& e)
            {
                std::cout  << e.get_error_code() << ": Ошибка ввода автора: " << e.what()  << std::endl;
            }
            catch (const title_validation_exception& e)
            {
                std::cout  << e.get_error_code() << ": Ошибка ввода названия: " << e.what()  << std::endl;
            }
            catch (const word_validation_exception& e)
            {
                std::cout  << e.get_error_code() << ": Ошибка ввода данных: " << e.what()  << std::endl;
            }
            catch (const number_validation_exception& e)
            {
                std::cout << e.get_error_code() << ": Ошибка ввода числового значения: " << e.what()  << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout  << " Ошибка при добавлении карточки: " << e.what()  << std::endl;
            }

            std::cout  << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 2: // Поиск по образцу
        {
            auto search_template = _create_search_template();

            if (!search_template.hasCriteria())
            {
                std::cout << "Не задано ни одного критерия поиска!"  << std::endl;
                break;
            }

            auto result = _search_by_template(search_template);
            if (result)
            {
                std::cout << "Найдено!" << std::endl;
                std::cout << result->getData() << std::endl;
            }
            else
            {
                std::cout << "Не найдено!" << std::endl;
            }

            std::cout << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 3: // Вывод по возрастанию
        {
            std::cout  << "\n=== ДЕРЕВО (ПО ВОЗРАСТАНИЮ) ===" << std::endl;
            T card;
            card.hat(std::cout);
            tree.printSortedAscending();

            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
            break;
        }

        case 4: // Вывод по убыванию
        {
            std::cout << "\n=== ДЕРЕВО (ПО УБЫВАНИЮ) ==="  << std::endl;
            T card;
            card.hat(std::cout);
            tree.printSortedDescending();

            std::cout<< "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 5: // Удаление узла
        {
            try
            {
                auto search_template = _create_search_template();

                if (!search_template.hasCriteria())
                {
                    std::cout<< "Не задано ни одного критерия поиска!" << std::endl;
                    break;
                }

                auto result = _search_by_template(search_template);
                if (result)
                {
                    tree.remove(result->getData());
                    std::cout  << " Узел удален!"<< std::endl;
                }
                else
                {
                    std::cout  << " Узел не найден!"  << std::endl;
                }
            }
            catch (const std::exception& e)
            {
                std::cout  << "Ошибка при удалении узла: " << e.what()  << std::endl;
            }

            std::cout << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 6: // Вывод дерева в pre-order
        {
            std::cout  << "\n=== ДЕРЕВО (PRE-ORDER) ===" << std::endl;
            T card;
            card.hat(std::cout);
            tree.printTree();

            std::cout  << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 7: // Поиск по любому полю
        {
            std::cout  << "\n=== ПОИСК ПО ЛЮБОМУ ПОЛЮ ==="  << std::endl;
            std::cout  << "Введите значение для поиска: ";
            std::string searchValue;
            std::getline(std::cin, searchValue);

            auto result = tree.find_if([&searchValue](const T& card)
                                       {
                                           if (card.getTitle() == searchValue ||
                                               card.getAuthor() == searchValue ||
                                               card.getInventoryNumber() == searchValue ||
                                               card.getThematicCode() == searchValue)
                                               return true;

                                           if (dynamic_cast<const ArticleCard*>(&card) != nullptr)
                                               return false;

                                           const auto* independentCard = dynamic_cast<const IndependentPublicationCard*>(&card);
                                           if (independentCard)
                                           {
                                               if (independentCard && independentCard->getPublisher() == searchValue)
                                                   return true;

                                               try
                                               {
                                                   int numValue = std::stoi(searchValue);
                                                   if (independentCard && (independentCard->getYearOfPublication() == numValue ||
                                                                           independentCard->getCirculation() == numValue ||
                                                                           independentCard->getPagesNamber() == numValue))
                                                       return true;
                                               }
                                               catch (const std::exception&) {
                                                   // Игнорируем ошибки преобразования строки в число
                                               }
                                           }
                                           return false;
                                       });

            if (result)
            {
                std::cout  << " Найдено!"  << std::endl;
                std::cout << result->getData() << std::endl;
            }
            else
            {
                std::cout  << " Не найдено!"  << std::endl;
            }

            std::cout  << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
        }

        case 8: // Операции с файлами
        {
            int fileChoice;
            do
            {
                system("cls");
                std::cout << "\n=== ОПЕРАЦИИ С ФАЙЛАМИ ===" << "\033[0m"
                          << "\n1. Запись в текстовый файл"
                          << "\n2. Чтение из текстового файла"
                          << "\n3. Запись в бинарный файл"
                          << "\n4. Чтение из бинарного файла"
                          << "\n5. Возврат в меню " << className << "\n\nВаш выбор: \033[0m";

                fileChoice = _getUserChoice();

                switch(fileChoice)
                {
                    case 1:
                        _writeToTextFile();
                        break;
                    case 2:
                        _readFromTextFile();
                        break;
                    case 3:
                        _writeToBinaryFile();
                        break;
                    case 4:
                        _readFromBinaryFile();
                        break;
                    case 5:
                        std::cout  << "Возврат в меню " << className << "..." << std::endl;
                        break;
                    default:
                        std::cout  << "Неверный выбор!"  << std::endl;
                }

                if (fileChoice != 5)
                {
                    std::cout << "\033[36m" << "\n\nНажмите Enter для продолжения..." << "\033[0m";
                    std::cin.get();

                    std::cin.get();
                }

            } while (fileChoice != 5);
            break;
        }

        case 9: // Выход в главное меню
            std::cout  << " Возврат в главное меню..." << std::endl;
            std::cin.get();
            break;

        default:
            std::cout  <<  "Неверный выбор!" << std::endl;
            std::cout  << "\nНажмите Enter для продолжения..." ;
            std::cin.get();
            break;
    }
}

// Реализации ваших оригинальных методов
template<class T>
std::function<bool(const T&, const T&)> LibraryManager<T>::_choose_comparator()
{
    int sortChoice;
    std::cout << "\n=== ВЫБОР ПОЛЯ ДЛЯ СОРТИРОВКИ ==="  << std::endl;
    std::cout << "\n1. По названию (по умолчанию)"
              << "\n2. По автору"
              << "\n3. По инвентарному номеру"
              << "\n4. По тематическому коду";

    if (className != "ArticleCard")
    {
        std::cout << "\n5. По году издания"
                  << "\n6. По издателю"
                  << "\n7. По тиражу"
                  << "\n8. По количеству страниц";
    }

    std::cout
               << "\n\nВаш выбор: ";

    if (!(std::cin >> sortChoice))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout  << "Неверный ввод. Используется сортировка по названию.\n" ;
        return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };
    }

    std::cin.ignore();

    switch(sortChoice)
    {
        case 1:
            return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };
        case 2:
            return [](const T& a, const T& b) { return a.getAuthor() < b.getAuthor(); };
        case 3:
            return [](const T& a, const T& b) { return a.getInventoryNumber() < b.getInventoryNumber(); };
        case 4:
            return [](const T& a, const T& b) { return a.getThematicCode() < b.getThematicCode(); };
        case 5:
            if (className != "ArticleCard")
            {
                return [](const T& a, const T& b)
                {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB)
                        return cardA->getYearOfPublication() < cardB->getYearOfPublication();
                    return a.getTitle() < b.getTitle();
                };
            }
            break;
        case 6:
            if (className != "ArticleCard")
            {
                return [](const T& a, const T& b)
                {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB)
                        return cardA->getPublisher() < cardB->getPublisher();
                    return a.getTitle() < b.getTitle();
                };
            }
            break;
        case 7:
            if (className != "ArticleCard")
            {
                return [](const T& a, const T& b)
                {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB)
                        return cardA->getCirculation() < cardB->getCirculation();
                    return a.getTitle() < b.getTitle();
                };
            }
            break;
        case 8:
            if (className != "ArticleCard")
            {
                return [](const T& a, const T& b)
                {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB)
                        return cardA->getPagesNamber() < cardB->getPagesNamber();
                    return a.getTitle() < b.getTitle();
                };
            }
            break;
    }

    std::cout << "Неверный выбор. Используется сортировка по названию.\n";
    return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };
}

template<class T>
SearchTemplate LibraryManager<T>::_create_search_template()
{
    SearchTemplate search_template;
    std::cin.ignore();

    std::cout << "\n=== СОЗДАНИЕ ОБРАЗЦА ДЛЯ ПОИСКА ===" <<std::endl;
    std::cout << "Заполните поля для поиска (оставьте пустыми или 0 для пропуска):" << std::endl;

    std::cout << "Введите название (оставьте пустым для пропуска): ";
    std::string title;
    std::getline(std::cin, title);
    search_template.setTitle(title);

    std::cout << "Введите автора (оставьте пустым для пропуска): ";
    std::string author;
    std::getline(std::cin, author);
    search_template.setAuthor(author);

    std::cout << "Введите авторский код (оставьте пустым для пропуска): ";
    std::string authorCode;
    std::getline(std::cin, authorCode);
    search_template.setAuthorMark(authorCode);

    std::cout << "Введите инвентарный номер (оставьте пустым для пропуска): ";
    std::string inventory;
    std::getline(std::cin, inventory);
    search_template.setInventoryNumber(inventory);

    std::cout << "Введите тематический код (оставьте пустым для пропуска): ";
    std::string thematic;
    std::getline(std::cin, thematic);
    search_template.setThematicCode(thematic);

    // Для производных классов добавляем дополнительные поля
    if (className != "ArticleCard") {
        std::cout << "Введите год издания (0 для пропуска): ";
        std::string yearStr;
        std::getline(std::cin, yearStr);
        try {
            if (!yearStr.empty()) {
                search_template.setYearOfPublication(std::stoi(yearStr));
            }
        } catch (...) {
            std::cout << "Некорректный год, поле будет пропущено" << std::endl;
        }

        std::cout << "Введите издателя (оставьте пустым для пропуска): ";
        std::string publisher;
        std::getline(std::cin, publisher);
        search_template.setPublisher(publisher);

        std::cout << "Введите тираж (0 для пропуска): ";
        std::string circulationStr;
        std::getline(std::cin, circulationStr);
        try {
            if (!circulationStr.empty()) {
                search_template.setCirculation(std::stoi(circulationStr));
            }
        } catch (...) {
            std::cout  << "Некорректный тираж, поле будет пропущено" << std::endl;
        }

        std::cout << "Введите количество страниц (0 для пропуска): ";
        std::string pagesStr;
        std::getline(std::cin, pagesStr);
        try {
            if (!pagesStr.empty()) {
                search_template.setPagesNamber(std::stoi(pagesStr));
            }
        } catch (...) {
            std::cout  << "Некорректное количество страниц, поле будет пропущено" << std::endl;
        }
    }

    return search_template;
}

template<class T>
treeNode<T>* LibraryManager<T>::_search_by_template(const SearchTemplate& search_template)
{
    return tree.find_if([&search_template, this](const T& card) {
        // Проверка базовых полей LibraryCard
        if (!search_template.getTitle().empty() && card.getTitle() != search_template.getTitle())
            return false;
        if (!search_template.getAuthor().empty() && card.getAuthor() != search_template.getAuthor())
            return false;
        if (!search_template.getAuthorMark().empty() && card.getAuthorMark() != search_template.getAuthorMark())
            return false;
        if (!search_template.getInventoryNumber().empty() && card.getInventoryNumber() != search_template.getInventoryNumber())
            return false;
        if (!search_template.getThematicCode().empty() && card.getThematicCode() != search_template.getThematicCode())
            return false;

        // Для ArticleCard поиск завершается на базовых полях
        if (dynamic_cast<const ArticleCard*>(&card) != nullptr)
            return true;

        // Проверка полей IndependentPublicationCard
        return this->_search_independent_fields(search_template, card);
    });
}

template<class T>
bool LibraryManager<T>::_search_independent_fields(const SearchTemplate& search_template, const T& card)
{
    const IndependentPublicationCard* indCard = dynamic_cast<const IndependentPublicationCard*>(&card);
    if (!indCard)
        return true;

    if (!search_template.getPublisher().empty() &&
        indCard->getPublisher() != search_template.getPublisher())
        return false;

    if (search_template.getYearOfPublication() != 0 &&
        indCard->getYearOfPublication() != search_template.getYearOfPublication())
        return false;

    if (search_template.getCirculation() != 0 &&
        indCard->getCirculation() != search_template.getCirculation())
        return false;

    if (search_template.getPagesNamber() != 0 &&
        indCard->getPagesNamber() != search_template.getPagesNamber())
        return false;

    return true;
}

template<class T>
void LibraryManager<T>::_writeToTextFile()
{
    try
    {
        std::string filename;
        std::cout << "\033[36m" << "Введите имя текстового файла: " << "\033[0m";
        std::getline(std::cin, filename);

        File_text<T> file_txt(filename);
        std::string type_id = _get_card_type_string();

        if (type_id == "UNKNOWN_CARD")
            throw std::runtime_error("Неизвестный тип карточки для менеджера: " + className);

        file_txt.Open_file_out();

        std::vector<T> sortedData = tree.getSortedAscending();
        if (sortedData.empty())
        {
            std::cout << "\033[33m" << "Нет данных для записи" << "\033[0m" << std::endl;
            return;
        }

        file_txt << type_id;

        for (auto& card : sortedData)
            file_txt.Write_record_in_file_text(card);

        std::cout << "\033[32m" << "Данные успешно записаны в текстовый файл: " << filename
                  << " (записано " << sortedData.size() << " карточек)" << "\033[0m" << std::endl;
    }
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка записи: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Неизвестная ошибка при записи в файл: " << e.what() << "\033[0m" << std::endl;
    }
}

template<class T>
void LibraryManager<T>::_readFromTextFile()
{
    try
    {
        std::string filename;
        std::cout << "\033[36m" << "Введите имя текстового файла: " << "\033[0m";
        std::getline(std::cin, filename);

        File_text<T> file_txt(filename);
        std::string expected_type_id = _get_card_type_string();

        file_txt.Open_file_in();

        std::string file_type_id;
        file_txt.Read_string_line(file_type_id);

        if (file_type_id != expected_type_id)
            throw file_format_exception(
                    "Несоответствие типов данных. Ожидался: " + expected_type_id +
                    ", найден: " + file_type_id, FILE_FORMAT_ERROR);

        int cardsAdded = 0;
        bool hasError = false;
        std::string errorMessage;

        while (true)
        {
            T card;
            try
            {
                file_txt.Read_record_in_file_text(card);
            }
            catch (const std::runtime_error& e)
            {
                std::string errorMsg = e.what();
                if (errorMsg.find("Конец файла") != std::string::npos ||
                    errorMsg.find("end of file") != std::string::npos)
                    break;
                hasError = true;
                errorMessage = e.what();
                break;
            }
            catch (const std::exception& e)
            {
                hasError = true;
                errorMessage = e.what();
                break;
            }

            try
            {
                tree.push(card);
                cardsAdded++;
                std::cout << "\033[33m" << "Загружена карточка #" << cardsAdded << "\033[0m" << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "\033[33m" << "Предупреждение: ошибка при добавлении карточки: " << e.what() << "\033[0m" << std::endl;
            }
        }

        if (cardsAdded > 0)
        {
            std::cout << "\033[32m" << "Успешно загружено " << cardsAdded << " карточек из текстового файла: " << filename << "\033[0m" << std::endl;
            if (hasError)
                std::cout << "\033[33m" << "Предупреждение: " << errorMessage << "\033[0m" << std::endl;
        }
        else {
            std::cout << "\033[33m" << "Не загружено ни одной карточки из файла: " << filename << "\033[0m" << std::endl;
            if (hasError)
                throw file_access_exception("Ошибка чтения файла: " + errorMessage, FILE_ACCESS_ERROR);
        }
    }
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка чтения: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Неизвестная ошибка при чтении файла: " << e.what() << "\033[0m" << std::endl;
    }
}

template<class T>
void LibraryManager<T>::_writeToBinaryFile()
{
    try
    {
        std::string filename;
        std::cout << "\033[36m" << "Введите имя бинарного файла: " << "\033[0m";
        std::getline(std::cin, filename);

        File_binary<T> file_bin(filename);

        CardType expected_type = _get_card_type();
        if (expected_type == CardType::UNKNOWN)
            throw std::runtime_error("Неизвестный тип карточки для менеджера: " + className);

        int type_code = static_cast<int>(expected_type);
        std::vector<T> sortedData = tree.getSortedAscending();

        if (sortedData.empty())
        {
            std::cout << "\033[33m" << "Нет данных для записи" << "\033[0m" << std::endl;
            return;
        }

        file_bin.Open_for_write();
        file_bin.Clear_file();

        for (auto& card : sortedData)
        {
            file_bin << type_code;      // Записываем тип карточки
            file_bin << card;           // Записываем саму карточку
        }

        std::cout << "\033[32m" << "Данные успешно записаны в бинарный файл: " << filename
                  << " (записано " << sortedData.size() << " карточек)" << "\033[0m" << std::endl;
    }
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка записи: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Неизвестная ошибка при записи в бинарный файл: " << e.what() << "\033[0m" << std::endl;
    }
}

template<class T>
void LibraryManager<T>::_readFromBinaryFile()
{
    try
    {
        std::string filename;
        std::cout << "\033[36m" << "Введите имя бинарного файла: " << "\033[0m";
        std::getline(std::cin, filename);

        File_binary<T> file_bin(filename);
        CardType expected_type = _get_card_type();

        if (expected_type == CardType::UNKNOWN)
            throw std::runtime_error("Неизвестный тип карточки для менеджера: " + className);

        int expected_type_code = static_cast<int>(expected_type);
        file_bin.Open_for_read();

        int cardsAdded = 0;
        bool hasError = false;
        std::string errorMessage;

        while (true)
        {
            try {
                T card;
                int file_type_code = 0;

                file_bin >> file_type_code;

                if (file_type_code != expected_type_code)
                    throw file_format_exception(
                            "Несоответствие типов данных. Ожидался ID: " +
                            std::to_string(expected_type_code) + ", найден ID: " +
                            std::to_string(file_type_code), FILE_FORMAT_ERROR);

                file_bin >> card;

                tree.push(card);
                cardsAdded++;
                std::cout << "\033[33m" << "Загружена карточка #" << cardsAdded << "\033[0m" << std::endl;
            }
            catch (const std::runtime_error& e)
            {
                // Конец файла - нормальный выход
                std::string errorMsg = e.what();
                if (errorMsg.find("Конец файла") != std::string::npos ||
                    errorMsg.find("end of file") != std::string::npos)
                    break;
                hasError = true;
                errorMessage = e.what();
                break;
            }
            catch (const file_format_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": " << e.what() << "\033[0m" << std::endl;
                break;
            }
        }

        if (cardsAdded > 0)
        {
            std::cout << "\033[32m" << "Успешно загружено " << cardsAdded
                      << " карточек из бинарного файла: " << filename << "\033[0m" << std::endl;

            if (hasError)
                std::cout << "\033[33m" << "Предупреждение: " << errorMessage << "\033[0m" << std::endl;
        }
        else
            std::cout << "\033[33m" << "Не загружено ни одной карточки из файла: "
                      << filename << "\033[0m" << std::endl;
    }
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка чтения: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Неизвестная ошибка при чтении бинарного файла: " << e.what() << "\033[0m" << std::endl;
    }
}

template<class T>
CardType LibraryManager<T>::_get_card_type()
{
    if (className == "ArticleCollectionCard") return ARTICLE_COLLECTION_CARD;
    if (className == "BookCard") return BOOK_CARD;
    if (className == "ArticleCard") return ARTICLE_CARD;
    return UNKNOWN;

}

template<class T>
std::string LibraryManager<T>::_get_card_type_string() const
{
    if (className == "ArticleCollectionCard") return "ArticleCollectionCard";
    if (className == "BookCard") return "BookCard";
    if (className == "ArticleCard") return "ArticleCard";
    return "UNKNOWN_CARD";
}

// Явные инстанциации
template class LibraryManager<ArticleCollectionCard>;
template class LibraryManager<BookCard>;
template class LibraryManager<ArticleCard>;