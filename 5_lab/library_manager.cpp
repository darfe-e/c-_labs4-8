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
    std::cout << "\033[35m" << "\n=== РАБОТА С " << className << " ===" << "\033[0m"
              << "\033[33m"
              << "\n\n1. Добавить карточку"
              << "\n2. Найти карточку по нескольким полям"
              << "\n3. Вывести отсортированное по возрастанию дерево"
              << "\n4. Вывести отсортированное по убыванию дерево"
              << "\n5. Удалить узел с заданной характеристикой"
              << "\n6. Вывести дерево (pre-order)"
              << "\n7. Поиск по условию (find_if)"
              << "\n8. Операции с файлами"
              << "\n9. Вернуться в главное меню"
              << "\033[0m"
              << "\033[32m" << "\n\nВаш выбор: " << "\033[0m";
}

template<class T>
int LibraryManager<T>::_getUserChoice()
{
    int choice;
    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        throw std::runtime_error("Неверный ввод. Пожалуйста, введите число.");
    }
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
            std::cout << "\033[31m" << e.what() << "\033[0m" << std::endl;
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
            std::cin.ignore();
            std::cout << "\033[36m" << "\n=== ДОБАВЛЕНИЕ КАРТОЧКИ ===" << "\033[0m" << std::endl;

            try
            {
                std::cin >> card;
                tree.push(card);
                std::cout << "\033[32m" << "\nКарточка успешно добавлена!" << "\033[0m" << std::endl;
            }
            catch (const author_validation_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": Ошибка ввода автора: " << e.what() << "\033[0m" << std::endl;
            }
            catch (const title_validation_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": Ошибка ввода названия: " << e.what() << "\033[0m" << std::endl;
            }
            catch (const word_validation_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": Ошибка ввода данных: " << e.what() << "\033[0m" << std::endl;
            }
            catch (const year_validation_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": Ошибка ввода года: " << e.what() << "\033[0m" << std::endl;
            }
            catch (const number_validation_exception& e)
            {
                std::cout << "\033[31m" << e.get_error_code() << ": Ошибка ввода числового значения: " << e.what() << "\033[0m" << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "\033[31m" << "\nОшибка при добавлении карточки: " << e.what() << "\033[0m" << std::endl;
            }
            break;
        }

        case 2: // Поиск по образцу
        {
            auto search_template = _create_search_template();
            bool has_search_criteria = _has_criterias(search_template);

            if (!has_search_criteria)
            {
                std::cout << "\033[31m" << "\nНе задано ни одного критерия поиска!" << "\033[0m" << std::endl;
                break;
            }

            auto result = _search_by_template(search_template);
            if (result)
            {
                std::cout << "\033[32m" << "\nНайдено!" << "\033[0m" << std::endl;
                std::cout << result->getData() << std::endl;
            }
            else
                std::cout << "\033[31m" << "\nНе найдено!" << "\033[0m" << std::endl;
            break;
        }

        case 3: // Вывод по возрастанию
        {
            std::cout << "\033[36m" << "\nДерево (по возрастанию):" << "\033[0m" << std::endl;
            T card;
            card.hat(std::cout);
            tree.printSortedAscending();
            std::cin.get();
            break;
        }

        case 4: // Вывод по убыванию
        {
            std::cout << "\033[36m" << "\nДерево (по убыванию):" << "\033[0m" << std::endl;
            T card;
            card.hat(std::cout);
            tree.printSortedDescending();
            std::cin.get();
            break;
        }

        case 5: // Удаление узла
        {
            try
            {
                auto search_template = _create_search_template();
                bool has_search_criteria = _has_criterias(search_template);

                if (!has_search_criteria)
                {
                    std::cout << "\033[31m" << "\nНе задано ни одного критерия поиска!" << "\033[0m" << std::endl;
                    break;
                }

                auto result = _search_by_template(search_template);
                if (result)
                {
                    tree.remove(result->getData());
                    std::cout << "\033[32m" << "Узел удален!" << "\033[0m" << std::endl;
                }
                else
                    std::cout << "\033[31m" << "Узел не найден!" << "\033[0m" << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "\033[31m" << "\nОшибка при удалении узла: " << e.what() << "\033[0m" << std::endl;
            }
            std::cin.get();
            break;
        }

        case 6: // Вывод дерева в pre-order
        {
            std::cout << "\033[36m" << "\nДерево (pre-order):" << "\033[0m" << std::endl;
            T card;
            card.hat(std::cout);
            tree.printTree();
            std::cin.get();
            break;
        }

        case 7: // Поиск по любому полю
        {
            std::cout << "\033[36m" << "\nВведите значение для поиска по любому полу: " << "\033[0m";
            std::string searchValue;
            std::cin.ignore();
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

                                               int numValue = std::stoi(searchValue);
                                               if (independentCard && (independentCard->getYearOfPublication() == numValue ||
                                                                       independentCard->getCirculation() == numValue ||
                                                                       independentCard->getPagesNamber() == numValue))
                                                   return true;
                                           }
                                           return false;
                                       });

            if (result)
            {
                std::cout << "\033[32m" << "\nНайдено!\n" << "\033[0m";
                std::cout << result->getData() << std::endl;
            }
            else
                std::cout << "\033[31m" << "\nНе найдено!" << "\033[0m" << std::endl;

            std::cin.get();
            break;
        }

        case 8: // Операции с файлами
        {
            int fileChoice;
            do
            {
                system("cls");
                std::cout << "\033[35m" << "\n=== ОПЕРАЦИИ С ФАЙЛАМИ ===" << "\033[0m"
                          << "\033[33m"
                          << "\n\n1. Запись в текстовый файл"
                          << "\n2. Чтение из текстового файла"
                          << "\n3. Запись в бинарный файл"
                          << "\n4. Чтение из бинарного файла"
                          << "\n5. Возврат в меню " << className
                          << "\033[0m"
                          << "\033[32m" << "\n\nВаш выбор: " << "\033[0m";

                fileChoice = _getUserChoice();

                switch(fileChoice)
                {
                    case 1: _writeToTextFile(); break;
                    case 2: _readFromTextFile(); break;
                    case 3: _writeToBinaryFile(); break;
                    case 4: _readFromBinaryFile(); break;
                    case 5: break;
                    default: std::cout << "\033[31m" << "Неверный выбор!" << "\033[0m" << std::endl;
                }

                if (fileChoice != 5)
                {
                    std::cout << "\033[36m" << "\nНажмите Enter для продолжения..." << "\033[0m";
                    std::cin.ignore();
                    std::cin.get();
                }

            } while (fileChoice != 5);
            break;
        }

        case 9: // Выход в главное меню
            std::cout << "\033[34m" << "Возврат в главное меню..." << "\033[0m" << std::endl;
            std::cin.get();
            break;

        default:
            std::cout << "\033[31m" << "Неверный выбор!" << "\033[0m" << std::endl;
    }
}

// Реализации ваших оригинальных методов
template<class T>
std::function<bool(const T&, const T&)> LibraryManager<T>::_choose_comparator()
{
    int sortChoice;
    std::cout << "\033[36m" << "\n=== ВЫБОР ПОЛЯ ДЛЯ СОРТИРОВКИ ===" << "\033[0m" << std::endl;
    std::cout << "\033[33m"
              << "\n1. По названию (по умолчанию)"
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

    std::cout << "\033[0m"
              << "\033[32m" << "\n\nВаш выбор: " << "\033[0m";

    if (!(std::cin >> sortChoice))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "\033[31m" << "Неверный ввод. Используется сортировка по названию.\n" << "\033[0m";
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

    std::cout << "\033[31m" << "Неверный выбор. Используется сортировка по названию.\n" << "\033[0m";
    return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };
}

template<class T>
T LibraryManager<T>::_create_search_template()
{
    T search_template;
    std::cin.ignore();

    std::cout << "\033[36m" << "\n=== СОЗДАНИЕ ОБРАЗЦА ДЛЯ ПОИСКА ===" << "\033[0m" << std::endl;
    std::cout << "\033[33m" << "Заполните поля для поиска (оставьте пустыми или 0 для пропуска):" << "\033[0m" << std::endl;

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

    if (auto* indCard = dynamic_cast<IndependentPublicationCard*>(&search_template))
    {
        std::cout << "Введите год издания (0 для пропуска): ";
        std::string yearStr;
        std::getline(std::cin, yearStr);
        try
        {
            indCard->setYearOfPublication(std::stoi(yearStr));
        }
        catch (...)
        {
            std::cout << "\033[33m" << "Поле будет пропущено" << "\033[0m" << std::endl;
        }

        std::cout << "Введите издателя (оставьте пустым для пропуска): ";
        std::string publisher;
        std::getline(std::cin, publisher);
        indCard->setPublisher(publisher);

        std::cout << "Введите тираж (0 для пропуска): ";
        std::string circulationStr;
        std::getline(std::cin, circulationStr);
        try
        {
            indCard->setCirculation(std::stoi(circulationStr));
        }
        catch (...)
        {
            std::cout << "\033[33m" << "Поле будет пропущено" << "\033[0m" << std::endl;
        }

        std::cout << "Введите количество страниц (0 для пропуска): ";
        std::string pagesStr;
        std::getline(std::cin, pagesStr);
        try
        {
            indCard->setPagesNamber(std::stoi(pagesStr));
        }
        catch (...)
        {
            std::cout << "\033[33m" << "Поле будет пропущено" << "\033[0m" << std::endl;
        }
    }

    return search_template;
}

template<class T>
treeNode<T>* LibraryManager<T>::_search_by_template(const T& search_template)
{
    // Явно захватываем this для вызова метода класса
    return tree.find_if([this, &search_template](const T& card)
                        {
                            if (!search_template.getTitle().empty() && card.getTitle() != search_template.getTitle())
                                return false;
                            if (!search_template.getAuthor().empty() && card.getAuthor() != search_template.getAuthor())
                                return false;
                            if (!search_template.getInventoryNumber().empty() && card.getInventoryNumber() != search_template.getInventoryNumber())
                                return false;
                            if (!search_template.getThematicCode().empty() && card.getThematicCode() != search_template.getThematicCode())
                                return false;

                            if (dynamic_cast<const ArticleCard*>(&card) != nullptr)
                                return true;

                            return this->_search_chosen(search_template, card);
                        });
}

template<class T>
bool LibraryManager<T>::_has_criterias(const T& search_template)
{
    bool has_search_criteria = !search_template.getTitle().empty() ||
                               !search_template.getAuthor().empty() ||
                               !search_template.getInventoryNumber().empty() ||
                               !search_template.getThematicCode().empty();

    if (!(className == "ArticleCard"))
    {
        // Используем const_cast для временного снятия константности
        const IndependentPublicationCard* indCard = dynamic_cast<const IndependentPublicationCard*>(&search_template);
        if (indCard)
        {
            has_search_criteria = has_search_criteria || indCard->getYearOfPublication() != 0;
            has_search_criteria = has_search_criteria || indCard->getCirculation() != 0;
            has_search_criteria = has_search_criteria || indCard->getPagesNamber() != 0;
            has_search_criteria = has_search_criteria || !indCard->getPublisher().empty();
        }
    }

    return has_search_criteria;
}

template<class T>
bool LibraryManager<T>::_search_chosen(const T& templateIndependent, const T& independentCard)
{
    const IndependentPublicationCard* templateInd = dynamic_cast<const IndependentPublicationCard*>(&templateIndependent);
    const IndependentPublicationCard* indCard = dynamic_cast<const IndependentPublicationCard*>(&independentCard);

    if (!templateInd || !indCard)
        return true;

    if (!templateInd->getPublisher().empty() &&
        indCard->getPublisher() != templateInd->getPublisher())
        return false;

    if (templateInd->getYearOfPublication() != 0 &&
        indCard->getYearOfPublication() != templateInd->getYearOfPublication())
        return false;

    if (templateInd->getCirculation() != 0 &&
        indCard->getCirculation() != templateInd->getCirculation())
        return false;

    if (templateInd->getPagesNamber() != 0 &&
        indCard->getPagesNamber() != templateInd->getPagesNamber())
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
        std::cin.ignore();
        std::getline(std::cin, filename);

        File_text<T> file_txt(filename);

        // 1. Получаем строковый ID типа
        std::string type_id = _get_card_type_string();
        if (type_id == "UNKNOWN_CARD")
            throw std::runtime_error("Unknown card type mapping for manager: " + className);

        // Открытие файла для записи (перезаписывает, если существует)
        if (!file_txt.Open_file_out())
        {
            throw file_open_exception("Не удалось открыть текстовый файл для записи: " + filename, FILE_OPEN_ERROR);
        }

        try
        {
            // Получаем все элементы в отсортированном порядке
            std::vector<T> sortedData = tree.getSortedAscending();

            if (sortedData.empty()) {
                std::cout << "\033[33m" << "Нет данных для записи" << "\033[0m" << std::endl;
                return;
            }

            // ЗАПИСЬ: Первой строкой записываем ID типа для всего файла
            // ПРЕДПОЛОЖЕНИЕ: File_text<T> перегружает оператор << для std::string и добавляет разделитель (например, newline).
            file_txt << type_id << "\n";

            // Записываем все карточки в файл
            for (auto& card : sortedData)
            {
                file_txt.Write_record_in_file_text(card);
            }

            std::cout << "\033[32m" << "Данные успешно записаны в текстовый файл: " << filename
                      << " (записанно " << sortedData.size() << " карточек)" << "\033[0m" << std::endl;
        }
        catch (const std::exception& e)
        {
            throw file_write_exception("Исключение при записи в текстовый файл: " + std::string(e.what()), FILE_WRITE_ERROR);
        }
    }
        // ... (Обработка исключений - остается без изменений) ...
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_write_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка записи: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка доступа: " << e.what() << "\033[0m" << std::endl;
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
        std::cin.ignore();
        std::getline(std::cin, filename);

        File_text<T> file_txt(filename);

        // 1. Получаем ожидаемый строковый ID типа
        std::string expected_type_id = _get_card_type_string();

        if (!file_txt.Open_file_in())
        {
            throw file_open_exception("Не удалось открыть текстовый файл для чтения: " + filename, FILE_OPEN_ERROR);
        }

        try
        {
            // 2. ИСПРАВЛЕНИЕ: Используем Read_string_line для чтения всего заголовка.
            std::string file_type_id;
            file_txt.Read_string_line(file_type_id); // Этот метод должен прочитать заголовок и перейти на следующую строку.

            if (file_type_id != expected_type_id)
            {
                throw FileTypeMismatchException(
                        "Несоответствие типов данных в текстовом файле. Ожидался: " + expected_type_id +
                        ", найден: " + file_type_id, FILE_FORMAT_ERROR);
            }
        }
        catch (const FileTypeMismatchException&) { throw; } // Переброс нашей ошибки
        catch (const std::runtime_error& e)
        {
            // Перехват "End of file reached when trying to read string."
            if (std::string(e.what()).find("End of file") != std::string::npos) {
                std::cout << "\033[33m" << "Файл пуст или содержит только заголовок." << "\033[0m" << std::endl;
                return;
            }
            throw file_read_exception("Ошибка при чтении заголовка (типа карточки) файла: " + std::string(e.what()), FILE_READ_ERROR);
        }
        catch (const std::exception& e)
        {
            // Ошибка чтения ID типа (например, пустой файл)
            throw file_read_exception("Ошибка при чтении заголовка (типа карточки) файла: " + std::string(e.what()), FILE_READ_ERROR);
        }


        int cardsAdded = 0;

        try
        {
            // Читаем данные из файла пока не достигнем конца
            while (true)
            {
                T card;

                try
                {
                    // ВАЖНО: Read_record_in_file_text ДОЛЖЕН выбрасывать исключение на EOF.
                    file_txt.Read_record_in_file_text(card);
                }
                catch (const std::runtime_error& e)
                {
                    // Предполагаем, что Read_record_in_file_text бросает исключение на EOF или ошибку
                    std::string errorMsg = e.what();
                    if (errorMsg.find("End of file") != std::string::npos ||
                        errorMsg.find("end of file") != std::string::npos) {
                        break; // Нормальный выход по концу файла
                    } else {
                        throw; // Проброс ошибки чтения
                    }
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

            if (cardsAdded > 0) {
                std::cout << "\033[32m" << "Успешно загружено " << cardsAdded << " карточек из текстового файла: " << filename << "\033[0m" << std::endl;
            } else {
                std::cout << "\033[33m" << "Не загружено ни одной карточки из файла: " << filename << "\033[0m" << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            // Перехват ошибок чтения/формата
            throw file_read_exception("Исключение при чтении текстового файла: " + std::string(e.what()), FILE_READ_ERROR);
        }
    }
        // ... (общая обработка исключений - остается без изменений) ...
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_read_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка чтения: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const FileTypeMismatchException& e)
    {
        std::cout << "\033[31m" << "ОШИБКА ФОРМАТА: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка доступа: " << e.what() << "\033[0m" << std::endl;
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
        std::cin.ignore();
        std::getline(std::cin, filename);

        File_binary<T> file_bin(filename);

        // 1. Получаем ID типа для записи
        CardType expected_type = _get_card_type();
        if (expected_type == CardType::UNKNOWN)
            throw std::runtime_error("Unknown card type mapping for manager: " + className);

        int type_code = static_cast<int>(expected_type);

        try
        {
            // Очищаем файл перед записью
            file_bin.Remote();

            // Получаем все элементы в отсортированном порядке
            std::vector<T> sortedData = tree.getSortedAscending();

            if (sortedData.empty()) {
                std::cout << "\033[33m" << "Нет данных для записи" << "\033[0m" << std::endl;
                return;
            }

            // Записываем все карточки в файл
            for (auto& card : sortedData)
            {
                // 2. ЗАПИСЬ: Сначала записываем int код типа
                // ПРЕДПОЛОЖЕНИЕ: File_binary<T> перегружает оператор << для int и записывает его в поток.
                file_bin << type_code;

                // 3. Затем записываем саму карточку
                file_bin.Write_record_in_file(card);
            }

            std::cout << "\033[32m" << "Данные успешно записаны в бинарный файл: " << filename
                      << " (записанно " << sortedData.size() << " карточек)" << "\033[0m" << std::endl;
        }
        catch (const std::exception& e)
        {
            throw file_write_exception("Исключение при записи в бинарный файл: " + std::string(e.what()), FILE_WRITE_ERROR);
        }
    }
        // ... (Обработка исключений - остается без изменений) ...
    catch (const file_open_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка открытия файла: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_write_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка записи: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_format_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка формата: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const file_access_exception& e)
    {
        std::cout << "\033[31m" << e.get_error_code() << ": Ошибка доступа: " << e.what() << "\033[0m" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Неизвестная ошибка при записи в бинарный файл: " << e.what() << "\033[0m" << std::endl;
    }
}

// ЧТЕНИЕ ИЗ БИНАРНОГО ФАЙЛА
template<class T>
void LibraryManager<T>::_readFromBinaryFile()
{
    try
    {
        std::string filename;
        std::cout << "\033[36m" << "Введите имя бинарного файла: " << "\033[0m";
        std::cin.ignore();
        std::getline(std::cin, filename);

        File_binary<T> file_bin(filename);

        // 1. Получаем ID типа, который ожидаем прочитать
        CardType expected_type = _get_card_type();
        if (expected_type == CardType::UNKNOWN) {
            throw std::runtime_error("Unknown card type mapping for manager: " + className);
        }

        // --- ИСПРАВЛЕНИЕ: Открываем файл ОДИН РАЗ перед чтением ---
        try
        {
            file_bin.Open_for_read();
        }
        catch (const std::runtime_error& e)
        {
            std::string errorMsg = e.what();
            if (errorMsg.find("File is empty") != std::string::npos) {
                std::cout << "\033[33m" << "Файл пуст" << "\033[0m" << std::endl;
                return;
            }
            throw; // Пробрасываем другие ошибки открытия
        }
        // -----------------------------------------------------------

        int cardsAdded = 0;
        int expected_type_code = static_cast<int>(expected_type);

        // Цикл будет продолжаться, пока не будет брошено исключение
        while (true)
        {
            T card;
            int file_type_code = 0;

            try
            {
                // 2. Считываем int код типа
                // ПРЕДПОЛОЖЕНИЕ: File_binary<T> перегружает оператор >> для int.
                file_bin >> file_type_code;

                // Если оператор >> для int не смог прочитать данные, это может быть EOF.
                // В зависимости от реализации File_binary, EOF может быть выброшен тут или на Read_record_in_file.
                // Если поток в состоянии ошибки после попытки чтения int, это EOF или повреждение.
                if (file_type_code == 0 && file_bin.R_end_file()) {
                    break; // Нормальный выход по концу файла
                }

                // Проверяем код
                if (file_type_code != expected_type_code)
                {
                    // Ошибка несоответствия типа данных
                    throw FileTypeMismatchException(
                            "Несоответствие типов данных в бинарном файле. Ожидался ID: " + std::to_string(expected_type_code) +
                            ", найден ID: " + std::to_string(file_type_code), FILE_FORMAT_ERROR);
                }

                // 3. Если код совпал, читаем сам объект
                file_bin.Read_record_in_file(card);

                tree.push(card);
                cardsAdded++;
                std::cout << "\033[33m" << "Загружена карточка #" << cardsAdded << "\033[0m" << std::endl;
            }
            catch (const FileTypeMismatchException& e)
            {
                std::cout << "\033[31m" << "ОШИБКА ТИПА ДАННЫХ В ФАЙЛЕ: " << e.what() << "\033[0m" << std::endl;
                break; // Прерываем чтение
            }
            catch (const std::exception& e)
            {
                std::string errorMsg = e.what();

                // Если это конец файла - это НОРМАЛЬНОЕ завершение цикла.
                if (errorMsg.find("End of file reached") != std::string::npos || errorMsg.find("End of file") != std::string::npos) {
                    break;
                }
                    // Любое другое исключение чтения - это ошибка
                else {
                    std::cout << "\033[31m" << "Ошибка чтения: " << errorMsg << "\033[0m" << std::endl;
                    break;
                }
            }
        }

        if (cardsAdded > 0) {
            std::cout << "\033[32m" << "Успешно загружено " << cardsAdded << " карточек из бинарного файла: " << filename << "\033[0m" << std::endl;
        } else {
            std::cout << "\033[33m" << "Не загружено ни одной карточки из файла: " << filename << "\033[0m" << std::endl;
        }
    }
        // ... (общая обработка исключений - остается без изменений) ...
    catch (const std::exception& e)
    {
        std::cout << "\033[31m" << "Ошибка при чтении бинарного файла: " << e.what() << "\033[0m" << std::endl;
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