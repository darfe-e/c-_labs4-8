#include "..\headers\ArticleCard.h"
#include <iostream>

ArticleCard:: ArticleCard(IndependentPublicationCard* publicationCard)            // Конструктор с параметром - указатель на издание
        : LibraryCard(*dynamic_cast<LibraryCard*>(publicationCard)),              // Инициализация базового класса: тематический код берется из издания
          article(publicationCard->getTitle(), publicationCard->getAuthor()),     // Инициализация статьи: название и автор из издания
          publicationCard(publicationCard)                                        // Инициализация указателя на издание переданным значением
{}

ArticleCard::ArticleCard(const ArticleCard& other)          // Конструктор копирования
        : LibraryCard(other)                                // Вызов конструктора копирования базового класса LibraryCard
        , article(other.article)                            // Временная инициализация статьи пустым объектом (исправлено бы на article(other.article))
        , publicationCard(other.publicationCard)            // Копирование указателя на издание из другого объекта (поверхностное копирование)
{}


void ArticleCard::setPublicationCard(IndependentPublicationCard* newPublicationCard)  // Метод установки указателя на издание
{
    publicationCard = newPublicationCard;                                             // Присвоение нового значения указателю на издание
}

ArticleCard& ArticleCard::operator=(const ArticleCard& other)                         // Оператор присваивания
{
    if (this != &other)                          // Проверка на самоприсваивание (защита от a = a)
    {
        LibraryCard::operator=(other);           // Вызов оператора присваивания базового класса LibraryCard
        article = other.article;                 // Копирование объекта статьи через оператор присваивания класса Article
        publicationCard = other.publicationCard; // Копирование указателя на издание (поверхностное копирование)
    }
    return *this;                                // Возврат ссылки на текущий объект для цепочки присваиваний
}

std::ostream& operator<<(std::ostream& os, ArticleCard& card)  // Дружественная функция - оператор вывода в поток
{
    os << *card.publicationCard;                               // Разыменование указателя и вывод объекта издания через его оператор <<
    return os;                                                 // Возврат потока для поддержки цепочки вывода
}

std::istream& operator>>(std::istream& is, ArticleCard& card)     // Дружественная функция - оператор ввода из потока
{
    IndependentPublicationCard tempPublication;                   // Создаем временное издание для ввода данных

    std::cout << "\n\n=== Ввод данных издания ===" << std::endl;  // Заголовок для этапа ввода издания
    is >> tempPublication;                                        // Ввод данных издания через оператор >> IndependentPublicationCard

    // автоматически копирует все данные в карточку статьи
    card.setAuthor(tempPublication.getAuthor());                  // Установка автора из временного издания
    card.setTitle(tempPublication.getTitle());                    // Установка названия из временного издания
    card.setAuthorMark(tempPublication.getAuthorMark());          // Установка авторского знака из временного издания
    card.setInventoryNumber(tempPublication.getInventoryNumber());// Установка инвентарного номера из временного издания
    card.setThematicCode(tempPublication.getThematicCode());      // Установка тематического кода из временного издания

    if (card.publicationCard != nullptr) delete card.publicationCard;              // Освобождение памяти предыдущего издания, если оно существует
    card.publicationCard = new IndependentPublicationCard(tempPublication);        // Создание нового издания в куче

    Article tempArticle(tempPublication.getTitle(), tempPublication.getAuthor());  // Создание статьи с названием и автором из издания
    card.setArticle(tempArticle);                                                  // Установка созданной статьи в карточку

    std::cout << "\nArticleCard создан автоматически из данных издания!" << std::endl;  // Информационное сообщение

    return is;                                                        // Возврат потока для поддержки цепочки ввода
}

template<typename T>
bool operator== (ArticleCard& card, T value)
{
    return (static_cast<LibraryCard&>(card) == value);
}



void ArticleCard::menu()                                              // Метод отображения меню операций
{
    LibraryCard::menu();                                              // Вызов метода menu базового класса для отображения базовых пунктов
    std::cout << "\n5. Get other values (article, publicationCard)";  // Дополнительный пункт меню: получение статьи и издания
    std::cout << "\n6. Set other values (article, publicationCard)";  // Дополнительный пункт меню: установка статьи и издания
}

void ArticleCard::hat(std::ostream &os)                               // Переопределение метода отоюражения шапки таблицы
{
    publicationCard->hat(os);
}
// Бинарный вывод
std::fstream& operator<<(std::fstream& fs, const ArticleCard& card)
{
    // Всегда записываем как IndependentPublicationCard для единообразия
    if (card.publicationCard != nullptr) {
        // Записываем данные из publicationCard
        fs << static_cast<const LibraryCard&>(*card.publicationCard);

        size_t len = card.publicationCard->getPublisher().size();
        fs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) {
            fs.write(card.publicationCard->getPublisher().c_str(), len);
        }

        int year = card.publicationCard->getYearOfPublication();
        int circulation = card.publicationCard->getCirculation();
        int pages = card.publicationCard->getPagesNamber();

        fs.write(reinterpret_cast<const char*>(&year), sizeof(year));
        fs.write(reinterpret_cast<const char*>(&circulation), sizeof(circulation));
        fs.write(reinterpret_cast<const char*>(&pages), sizeof(pages));
    } else {
        // Записываем только базовые поля LibraryCard
        fs << static_cast<const LibraryCard&>(card);

        // Записываем пустые поля для IndependentPublicationCard
        size_t len = 0;
        fs.write(reinterpret_cast<const char*>(&len), sizeof(len));

        int zero = 0;
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
        fs.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    }

    return fs;
}

// Бинарный ввод
std::fstream& operator>>(std::fstream& fs, ArticleCard& card)
{
    // Сначала читаем базовые поля LibraryCard
    LibraryCard tempLibraryCard;
    fs >> tempLibraryCard;
    if (fs.fail()) return fs;

    // Читаем дополнительные поля IndependentPublicationCard
    size_t len;
    fs.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    std::string publisher;
    if (len > 0) {
        std::vector<char> buffer(len + 1);
        fs.read(buffer.data(), len);
        if (fs.fail() || fs.eof()) {
            fs.setstate(std::ios::failbit);
            return fs;
        }
        buffer[len] = '\0';
        publisher = buffer.data();
    }

    int yearOfPublication, circulation, pagesNamber;
    fs.read(reinterpret_cast<char*>(&yearOfPublication), sizeof(yearOfPublication));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    fs.read(reinterpret_cast<char*>(&circulation), sizeof(circulation));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    fs.read(reinterpret_cast<char*>(&pagesNamber), sizeof(pagesNamber));
    if (fs.fail() || fs.eof()) {
        fs.setstate(std::ios::failbit);
        return fs;
    }

    // Копируем данные в базовые поля ArticleCard
    card.setAuthor(tempLibraryCard.getAuthor());
    card.setTitle(tempLibraryCard.getTitle());
    card.setAuthorMark(tempLibraryCard.getAuthorMark());
    card.setInventoryNumber(tempLibraryCard.getInventoryNumber());
    card.setThematicCode(tempLibraryCard.getThematicCode());

    // Создаем новый publicationCard если есть данные
    if (card.publicationCard != nullptr) {
        delete card.publicationCard;
    }

    // Создаем publicationCard только если есть значимые данные
    if (!publisher.empty() || yearOfPublication != 0 || circulation != 0 || pagesNamber != 0) {
        card.publicationCard = new IndependentPublicationCard(
                publisher, yearOfPublication, circulation, pagesNamber,
                tempLibraryCard.getTitle(), tempLibraryCard.getAuthor(),
                tempLibraryCard.getAuthorMark(), tempLibraryCard.getInventoryNumber(),
                tempLibraryCard.getThematicCode()
        );
    } else {
        card.publicationCard = nullptr;
    }

    return fs;
}
// Текстовый вывод
std::ofstream& operator<<(std::ofstream& ofs, const ArticleCard& card)
{
    // Если есть publicationCard, используем его данные
    if (card.publicationCard != nullptr) {
        ofs << static_cast<const LibraryCard&>(*card.publicationCard);
        ofs << card.publicationCard->getPublisher() << "\n";
        ofs << card.publicationCard->getYearOfPublication() << "\n";
        ofs << card.publicationCard->getCirculation() << "\n";
        ofs << card.publicationCard->getPagesNamber() << "\n";
    } else {
        // Если publicationCard отсутствует, записываем только базовые поля
        ofs << static_cast<const LibraryCard&>(card);
        ofs << "\n"; // пустой publisher
        ofs << "0\n"; // yearOfPublication = 0
        ofs << "0\n"; // circulation = 0
        ofs << "0\n"; // pagesNamber = 0
    }

    // Записываем статью

    return ofs;
}

// Текстовый ввод
std::ifstream& operator>>(std::ifstream& ifs, ArticleCard& card)
{
    // Создаем временный объект для чтения данных
    IndependentPublicationCard tempPublication;

    // Читаем базовые поля LibraryCard
    ifs >> static_cast<LibraryCard&>(tempPublication);

    // Читаем дополнительные поля IndependentPublicationCard
    std::string publisher;
    int yearOfPublication, circulation, pagesNamber;

    std::getline(ifs, publisher); // publisher
    ifs >> yearOfPublication;
    ifs.ignore();
    ifs >> circulation;
    ifs.ignore();
    ifs >> pagesNamber;
    ifs.ignore();

    // Устанавливаем дополнительные поля
    tempPublication.setPublisher(publisher);
    tempPublication.setYearOfPublication(yearOfPublication);
    tempPublication.setCirculation(circulation);
    tempPublication.setPagesNamber(pagesNamber);

    // Копируем данные в базовые поля ArticleCard
    card.setAuthor(tempPublication.getAuthor());
    card.setTitle(tempPublication.getTitle());
    card.setAuthorMark(tempPublication.getAuthorMark());
    card.setInventoryNumber(tempPublication.getInventoryNumber());
    card.setThematicCode(tempPublication.getThematicCode());

    // Создаем новый publicationCard
    if (card.publicationCard != nullptr) {
        delete card.publicationCard;
    }
    card.publicationCard = new IndependentPublicationCard(tempPublication);

    // Читаем статью

    return ifs;
}