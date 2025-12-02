#include "..\file_headers\File_binary.h"
#include "iostream"
template<class T>
File_binary<T>::File_binary(const std::string& name) : File(name)
{
    validate_binary_file_extension(file_name);
}

template<class T>
File_binary<T>::~File_binary()
{
    if (file_stream.is_open())
        file_stream.close();
}

template<class T>
void File_binary<T>::Open_for_read()
{
    if (file_stream.is_open())
        file_stream.close();

    safe_open_for_binary_read(file_stream, file_name);

    check_file_not_empty(file_stream, file_name);

    file_stream.clear();
    file_stream.seekg(0, std::ios::beg);
}

template<class T>
void File_binary<T>::Open_for_write()
{
    if (file_stream.is_open())
        file_stream.close();

    safe_open_for_binary_write(file_stream, file_name);
}

template<class T>
void File_binary<T>::Close()
{
    if (file_stream.is_open())
        file_stream.close();
}

template<class T>
void File_binary<T>::Clear_file()
{
    safe_clear_file(file_name);
}

template<class T>
void File_binary<T>::Write_record_in_file(const T& OBJECT)
{
    check_file_opened_for_write(file_stream, file_name);
    file_stream << OBJECT;

    check_write_success(file_stream, file_name, "объекта");

    file_stream.flush();
}

template<class T>
void File_binary<T>::Read_record_in_file(T& OBJECT)
{
    check_file_opened_for_read(file_stream, file_name);
    file_stream.clear();

    check_not_end_of_file(file_stream, file_name);
    file_stream >> OBJECT;
    check_read_success(file_stream, file_name, "объекта");
}

template<class T>
File_binary<T>& File_binary<T>::operator<<(const T& obj)
{
    Write_record_in_file(obj);
    return *this;
}

template<class T>
File_binary<T>& File_binary<T>::operator>>(T& obj)
{
    Read_record_in_file(obj);
    return *this;
}

template<class T>
File_binary<T>& File_binary<T>::operator<<(int val)
{
    check_file_opened_for_write(file_stream, file_name);
    file_stream.write(reinterpret_cast<const char*>(&val), sizeof(int));
    check_write_success(file_stream, file_name, "целого числа");

    return *this;
}

template<class T>
File_binary<T>& File_binary<T>::operator>>(int& val)
{
    check_file_opened_for_read(file_stream, file_name);
    file_stream.read(reinterpret_cast<char*>(&val), sizeof(int));
    check_read_success(file_stream, file_name, "целого числа");

    return *this;
}

template class File_binary<BookCard>;
template class File_binary<ArticleCard>;
template class File_binary<ArticleCollectionCard>;
template class File_binary<IndependentPublicationCard>;