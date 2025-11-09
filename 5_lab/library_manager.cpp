#include "library_manager.h"
#include "headers/IndependentPublicationCard.h"
#include "headers/BookCard.h"
#include "headers/ArticleCard.h"
#include "headers/ArticleCollectionCard.h"
#include "headers/binryTree.h"

void main_menu_options()
{
    std::cout << "\033[36m" << "\n\nНажмите Enter для продолжения..." << "\033[0m";
    std::cin.get();
    system("cls");
    std::cout << "\033[35m" << "\n=== ГЛАВНОЕ МЕНЮ ===" << "\033[0m"
              << "\033[33m"
              << "\n\n1. Добавить карточку"
              << "\n2. Найти карточку по нескольким полям"
              << "\n3. Вывести отсортированное по возрастанию дерево"
              << "\n4. Вывести отсортированное по убыванию дерево"
              << "\n5. Удалить узел с заданной характеристикой"
              << "\n6. Вывести дерево (pre-order)"
              << "\n7. Поиск по условию (find_if)"
              << "\n8. Вернуться в главное меню"
              << "\033[0m"
              << "\033[32m" << "\n\nВаш выбор: " << "\033[0m";
}

// Шаблонная функция для обработки операций с деревом
template<typename T>
void handleTreeOperations(binaryTree<T>& tree, const std::string& treeName)
{
    int choice;

    std::cout << "\033[34m" << "\n=== РАБОТА С " << treeName << " ===" << "\033[0m" << std::endl;

    do
    {
        main_menu_options();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\033[31m" << "Неверный ввод. Пожалуйста, введите число.\n" << "\033[0m";
            continue;
        }

            switch(choice)
            {
                case 1: // Добавить карточку
                {
                    T card;
                    std::cin.ignore();
                    std::cout << "\033[36m" << "\n=== ДОБАВЛЕНИЕ КАРТОЧКИ ===" << "\033[0m" << std::endl;

                    try
                    {
                        std::cin >> card; // Ввод данных карточки
                        tree.push(card);
                        std::cout << "\033[32m" << "\nКарточка успешно добавлена!" << "\033[0m" << std::endl;
                    }
                    catch (const author_validation_exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка ввода автора: " << e.what() << "\033[0m" << std::endl;
                    }
                    catch (const title_validation_exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка ввода названия: " << e.what() << "\033[0m" << std::endl;
                    }
                    catch (const word_validation_exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка ввода данных: " << e.what() << "\033[0m" << std::endl;
                    }
                    catch (const year_validation_exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка ввода года: " << e.what() << "\033[0m" << std::endl;
                    }
                    catch (const number_validation_exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка ввода числового значения: " << e.what() << "\033[0m" << std::endl;
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << "\033[31m" << "\nОшибка при добавлении карточки: " << e.what() << "\033[0m" << std::endl;
                    }
                    break;
                }

                case 2: // Поиск по образцу
                {

                        auto search_template = create_search_template<T>();
                        bool has_search_criteria = has_criterias(search_template, treeName);

                        if (!has_search_criteria)
                        {
                            std::cout << "\033[31m" << "\nНе задано ни одного критерия поиска!" << "\033[0m" << std::endl;
                            break;
                        }

                        auto result = search_by_template(tree, search_template);

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
                        std::cout << "\033[36m" << "\nДерево (по возрастанию):" << "\033[0m" << std::endl;
                        tree.printSortedAscending();
                        std::cin.get();

                    break;

                case 4: // Вывод по убыванию
                        std::cout << "\033[36m" << "\nДерево (по убыванию):" << "\033[0m" << std::endl;
                        tree.printSortedDescending();
                        std::cin.get();

                    break;

                case 5: // Удаление узла
                {
                    try
                    {
                        auto search_template = create_search_template<T>();
                        bool has_search_criteria = has_criterias(search_template, treeName);

                        if (!has_search_criteria)
                        {
                            std::cout << "\033[31m" << "\nНе задано ни одного критерия поиска!" << "\033[0m" << std::endl;
                            break;
                        }

                        auto result = search_by_template(tree, search_template);

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

                case 6: // Вывод дерева

                        std::cout << "\033[36m" << "\nДерево (pre-order):" << "\033[0m" << std::endl;
                        tree.printTree();
                        std::cout << "\033[36m" << "\n\nНажмите Enter для продолжения..." << "\033[0m";
                        std::cin.get();

                    break;

                case 7: // Поиск по любому полю
                {

                        std::cout << "\033[36m" << "\nВведите значение для поиска по любому полю: " << "\033[0m";
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

                                                           try
                                                           {
                                                               int numValue = std::stoi(searchValue);
                                                               if (independentCard && (independentCard->getYearOfPublication() == numValue ||
                                                                                       independentCard->getCirculation() == numValue ||
                                                                                       independentCard->getPagesNamber() == numValue))
                                                                   return true;
                                                           }
                                                           catch (const std::exception&)
                                                           {
                                                               // Игнорируем ошибки преобразования - это нормально для строкового поиска
                                                           }
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

                case 8:
                    std::cout << "\033[34m" << "Возврат в главное меню..." << "\033[0m" << std::endl;
                    break;

                default:
                    std::cout << "\033[31m" << "Неверный выбор!" << "\033[0m" << std::endl;
            }

    } while (choice != 8);
}

template<typename T>
T create_search_template()
{
    T search_template;
    std::cin.ignore();

    std::cout << "\033[36m" << "\n=== СОЗДАНИЕ ОБРАЗЦА ДЛЯ ПОИСКА ===" << "\033[0m" << std::endl;
    std::cout << "\033[33m" << "Заполните поля для поиска (оставьте пустыми или 0 для пропуска):" << "\033[0m" << std::endl;

    // Ручной ввод полей без валидации
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
                std::cout << "\033[33m" << "Некорректный год, поле будет пропущено" << "\033[0m" << std::endl;
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
                std::cout << "\033[33m" << "Некорректный тираж, поле будет пропущено" << "\033[0m" << std::endl;
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
                std::cout << "\033[33m" << "Некорректное количество страниц, поле будет пропущено" << "\033[0m" << std::endl;
            }
    }

    return search_template;
}

template<typename T>
treeNode<T>* search_by_template(binaryTree<T>& tree, const T& search_template)
{
    return tree.find_if([&search_template](const T& card)  // Сделать константной
                        {
                            if (!search_template.getTitle().empty() && card.getTitle() != search_template.getTitle())
                                return false;
                            if (!search_template.getAuthor().empty() && card.getAuthor() != search_template.getAuthor())
                                return false;
                            if (!search_template.getInventoryNumber().empty() && card.getInventoryNumber() != search_template.getInventoryNumber())
                                return false;
                            if (!search_template.getThematicCode().empty() && card.getThematicCode() != search_template.getThematicCode())
                                return false;

                            // Для ArticleCard сразу возвращаем true
                            if (dynamic_cast<const ArticleCard*>(&card) != nullptr)
                                return true;

                            return search_chosen(search_template, card);
                        });
}


bool has_criterias(auto search_template, const std::string& treeName)
{
    bool has_search_criteria = !search_template.getTitle().empty() ||                    // Проверка названия
                               !search_template.getAuthor().empty() ||                   // Проверка автора
                               !search_template.getInventoryNumber().empty() ||          // Проверка инв. номера
                               !search_template.getThematicCode().empty();               // Проверка темат. кода

    if (!(treeName == "ArticleCard"))                                // Если не ArticleCard
    {
        IndependentPublicationCard* indCard = dynamic_cast<IndependentPublicationCard*>(&search_template);  // Приведение типа
        has_search_criteria = has_search_criteria || indCard->getYearOfPublication() != 0;  // Проверка года
        has_search_criteria = has_search_criteria || indCard->getCirculation() != 0;        // Проверка тиража
        has_search_criteria = has_search_criteria ||indCard->getPagesNamber() != 0;         // Проверка страниц
        has_search_criteria = has_search_criteria || !indCard->getPublisher().empty();      // Проверка издателя
    }

    return has_search_criteria;
}

template<typename T>
bool search_chosen(const T& templateIndependent, const T& independentCard)  // Оба константные
{
    const IndependentPublicationCard* templateInd = dynamic_cast<const IndependentPublicationCard*>(&templateIndependent);
    const IndependentPublicationCard* indCard = dynamic_cast<const IndependentPublicationCard*>(&independentCard);

    // Если хотя бы один не IndependentPublicationCard, пропускаем проверку
    if (!templateInd || !indCard)
        return true;

    // Проверка полей IndependentPublicationCard
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

template<typename T>
std::function<bool(const T&, const T&)> choose_comparator(const std::string& treeName)
{
    int sortChoice;

    std::cout << "\033[36m" << "\n=== ВЫБОР ПОЛЯ ДЛЯ СОРТИРОВКИ ===" << "\033[0m" << std::endl;
    std::cout << "\033[33m"
              << "\n1. По названию (по умолчанию)"
              << "\n2. По автору"
              << "\n3. По инвентарному номеру"
              << "\n4. По тематическому коду";

    // Добавляем дополнительные поля для соответствующих типов
    if (treeName != "ArticleCard")
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

    std::cin.ignore(); // Очистка буфера

    switch(sortChoice)
    {
        case 1: // По названию
            return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };

        case 2: // По автору
            return [](const T& a, const T& b) { return a.getAuthor() < b.getAuthor(); };

        case 3: // По инвентарному номеру
            return [](const T& a, const T& b) { return a.getInventoryNumber() < b.getInventoryNumber(); };

        case 4: // По тематическому коду
            return [](const T& a, const T& b) { return a.getThematicCode() < b.getThematicCode(); };

        case 5: // По году издания (только для IndependentPublicationCard и BookCard)
            if (treeName != "ArticleCard")
            {
                return [](const T& a, const T& b) {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB) {
                        return cardA->getYearOfPublication() < cardB->getYearOfPublication();
                    }
                    return a.getTitle() < b.getTitle(); // fallback
                };
            }
            break;

        case 6: // По издателю (только для IndependentPublicationCard и BookCard)
            if (treeName != "ArticleCard")
            {
                return [](const T& a, const T& b) {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB) {
                        return cardA->getPublisher() < cardB->getPublisher();
                    }
                    return a.getTitle() < b.getTitle(); // fallback
                };
            }
            break;

        case 7: // По тиражу (только для IndependentPublicationCard и BookCard)
            if (treeName != "ArticleCard")
            {
                return [](const T& a, const T& b) {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB) {
                        return cardA->getCirculation() < cardB->getCirculation();
                    }
                    return a.getTitle() < b.getTitle(); // fallback
                };
            }
            break;

        case 8: // По количеству страниц (только для IndependentPublicationCard и BookCard)
            if (treeName != "ArticleCard")
            {
                return [](const T& a, const T& b) {
                    const auto* cardA = dynamic_cast<const IndependentPublicationCard*>(&a);
                    const auto* cardB = dynamic_cast<const IndependentPublicationCard*>(&b);
                    if (cardA && cardB) {
                        return cardA->getPagesNamber() < cardB->getPagesNamber();
                    }
                    return a.getTitle() < b.getTitle(); // fallback
                };
            }
            break;
    }

    std::cout << "\033[31m" << "Неверный выбор. Используется сортировка по названию.\n" << "\033[0m";
    return [](const T& a, const T& b) { return a.getTitle() < b.getTitle(); };
}

template void handleTreeOperations<ArticleCollectionCard>(binaryTree<ArticleCollectionCard>&, const std::string&);
template void handleTreeOperations<BookCard>(binaryTree<BookCard>&, const std::string&);
template void handleTreeOperations<ArticleCard>(binaryTree<ArticleCard>&f, const std::string&);

template std::function<bool(const ArticleCollectionCard&, const ArticleCollectionCard&)>
choose_comparator<ArticleCollectionCard>(const std::string& treeName);

template std::function<bool(const BookCard&, const BookCard&)>
choose_comparator<BookCard>(const std::string& treeName);

template std::function<bool(const ArticleCard&, const ArticleCard&)>
choose_comparator<ArticleCard>(const std::string& treeName);