#include "..\headers\Catalog.h"

Catalog::Catalog(const Catalog& other)
        : libraryCards(nullptr), cardsCount(0), capacity(0)  // Инициализация полей нулевыми значениями в списке инициализации
{
    capacity = other.capacity;                       // Копирование значения вместимости из исходного объекта
    cardsCount = other.cardsCount;                   // Копирование количества карточек из исходного объекта

    if (capacity > 0)                                // Проверка, что исходный каталог не пустой
    {
        libraryCards = new LibraryCard*[capacity];   // Выделение памяти под массив указателей такой же вместимости

        for (int i = 0; i < cardsCount; i++)         // Цикл по всем существующим карточкам в исходном каталоге
            libraryCards[i] = other.libraryCards[i]; // Копирование указателей на карточки (поверхностное копирование)
    }
}

void Catalog::addCard(LibraryCard* libraryCard)
{
    if (cardsCount >= capacity)                                         // Проверка, достигнут ли предел вместимости массива
    {
        int newCapacity = (capacity == 0) ? 5 : capacity * 2;           // Вычисление новой вместимости: 5 если массив пустой, иначе удвоение
        LibraryCard** newLibraryCards = new LibraryCard*[newCapacity];  // Создание нового массива указателей с новой вместимостью

        for (int i = 0; i < cardsCount; i++)         // Цикл для копирования всех существующих указателей
            newLibraryCards[i] = libraryCards[i];    // Копирование указателей из старого массива в новый

        delete[] libraryCards;                       // Освобождение памяти старого массива указателей
        libraryCards = newLibraryCards;              // Присвоение указателя на новый массив
        capacity = newCapacity;                      // Обновление значения вместимости
    }

    libraryCards[cardsCount] = libraryCard;          // Добавление нового указателя в конец массива
    cardsCount++;                                    // Увеличение счетчика карточек после успешного добавления
}

Catalog& Catalog::operator=(const Catalog& other)
{
    if (this != &other)                              // Проверка на самоприсваивание
    {
        if (libraryCards) delete[] libraryCards;     // Освобождение памяти текущего массива, если он существует

        capacity = other.capacity;                   // Копирование вместимости из исходного объекта
        cardsCount = other.cardsCount;               // Копирование количества карточек из исходного объекта

        if (capacity > 0)                            // Проверка, что исходный каталог не пустой
        {
            libraryCards = new LibraryCard*[capacity];  // Выделение памяти под новый массив указателей
            for (int i = 0; i < cardsCount; i++) libraryCards[i] = other.libraryCards[i];  // Копирование всех указателей из исходного массива
        }
        else libraryCards = nullptr;                 // Если исходный каталог пустой, устанавливаем указатель в nullptr
    }
    return *this;                                    // Возврат ссылки на текущий объект для поддержки цепочки присваиваний
}

void Catalog::menu ()
{
    std::cout << "\nCatalog menu:\n"                          // Вывод заголовка меню каталога
              <<"\n1. Добавить библиотечную карточку;";       // Единственный пункт меню - добавление карточки
}