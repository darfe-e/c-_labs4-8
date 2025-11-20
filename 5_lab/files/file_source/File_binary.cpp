#include "..\file_headers\File_binary.h"
#include "iostream"
template<class T>

File_binary<T>::File_binary(const std::string& name) : File(name)
{
    // Не открываем файл в конструкторе - открываем при каждой операции
}

template<class T>
File_binary<T>::~File_binary()
{
    if(file_stream.is_open())
        file_stream.close();
}


template<class T>
void File_binary<T>::Remote()
{
    // Очищаем файл, открывая с trunc
    file_stream.open(file_name, std::ios::binary | std::ios::out | std::ios::trunc);
    if(file_stream.is_open())
    {
        file_stream.close();
    }
}


template<class T>
File_binary<T>& File_binary<T>::operator<<(T& obj)
{
    Write_record_in_file(obj);
    return *this;
}


template<class T>
void File_binary<T>::Write_record_in_file(const T& OBJECT)
{
    // Открываем только для записи (app)
    file_stream.open(file_name, std::ios::binary | std::ios::out | std::ios::app);
    if(!file_stream.is_open())
    {
        throw std::runtime_error("Cannot open file for writing: " + file_name);
    }
    // Очищаем флаги перед записью
    file_stream.clear();

    file_stream << OBJECT;

    if(file_stream.fail())
    {
        file_stream.close();
        throw std::runtime_error("Failed to write object to file: " + file_name);
    }

    file_stream.close(); // Закрываем после записи
}

template<class T>
void File_binary<T>::Open_for_read()
{
    // Закрываем, если был открыт
    if (file_stream.is_open())
        file_stream.close();

    // Открываем только для чтения
    file_stream.open(file_name, std::ios::binary | std::ios::in);
    if(!file_stream.is_open())
    {
        throw std::runtime_error("Cannot open file for reading: " + file_name);
    }

    // Проверяем, не пустой ли файл, перемещая указатель
    file_stream.seekg(0, std::ios::end);
    if (file_stream.tellg() == 0) {
        file_stream.close();
        throw std::runtime_error("File is empty: " + file_name);
    }

    // Возвращаем указатель в начало для старта чтения
    file_stream.seekg(0, std::ios::beg);
    file_stream.clear(); // Сбрасываем все флаги (на всякий случай)
}

// ФУНКЦИЯ ИЗМЕНЕНА
template<class T>
void File_binary<T>::Read_record_in_file(T& OBJECT)
{
    // Убираем открытие, так как файл должен быть открыт через Open_for_read()
    if(!file_stream.is_open())
    {
        throw std::runtime_error("File is not open for reading. Call Open_for_read() first.");
    }

    // Важно сбросить флаги перед попыткой чтения следующей записи
    file_stream.clear();

    file_stream >> OBJECT; // Читаем следующий объект

    // После попытки чтения:

    // 1. Если поток в состоянии ошибки, но не eof
    if (file_stream.fail() && !file_stream.eof()) {
        file_stream.close(); // Закрываем при ошибке
        throw std::runtime_error("Failed to read object from file: " + file_name);
    }

    // 2. Если достигнут конец файла (eof), возможно, после неудачной попытки чтения
    if (file_stream.eof()) {
        file_stream.close(); // Закрываем при достижении конца
        throw std::runtime_error("End of file reached");
    }

    // Убираем закрытие файла. Он остается открытым для следующего вызова.
    // file_stream.close();
}

template<class T>
bool File_binary<T>::R_end_file()
{
    if (!file_stream.is_open()) {
        return true;
    }

    // Упрощенный вариант, так как оператор >> устанавливает флаги
    return file_stream.eof();
}

template<class T>
File_binary<T>& File_binary<T>::operator>>(T& obj)
{
    // Обертка для чтения, предполагающая, что Open_for_read() был вызван
    Read_record_in_file(obj);
    return *this;
}


template<class T>
File_binary<T>& File_binary<T>::operator<<(const int& val)
{
    // Открываем только для записи (app)
    file_stream.open(file_name, std::ios::binary | std::ios::out | std::ios::app);
    if (!file_stream.is_open())
    {
        throw std::runtime_error("Cannot open file for writing int: " + file_name);
    }

    file_stream.clear(); // Сброс флагов перед записью

    // Запись int в бинарном режиме
    file_stream.write(reinterpret_cast<const char*>(&val), sizeof(int));

    if (file_stream.fail())
    {
        file_stream.close();
        throw std::runtime_error("Failed to write int to file: " + file_name);
    }

    file_stream.close(); // Закрываем после записи
    return *this;
}

template<class T>
File_binary<T>& File_binary<T>::operator>>(int& val)
{
    if (!file_stream.is_open())
    {
        throw std::runtime_error("File is not open for reading int. Call Open_for_read() first.");
    }

    file_stream.clear(); // Сброс флагов перед чтением

    // Проверяем, не достигли ли EOF перед попыткой чтения
    if (file_stream.peek() == EOF) {
        throw std::runtime_error("End of file reached");
    }

    // Чтение int в бинарном режиме
    file_stream.read(reinterpret_cast<char*>(&val), sizeof(int));

    // Проверка на EOF после попытки чтения
    if (file_stream.eof() && file_stream.gcount() == 0) {
        throw std::runtime_error("End of file reached"); // Чистый EOF
    }

    if (file_stream.fail() && !file_stream.eof())
    {
        throw std::runtime_error("Failed to read int from file (possible corruption)");
    }

    // Файл остается открытым.
    return *this;
}

template class File_binary<BookCard>;
template class File_binary<ArticleCard>;
template class File_binary<ArticleCollectionCard>;
template class File_binary<IndependentPublicationCard>;