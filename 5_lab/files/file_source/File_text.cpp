#include "..\file_headers\File_text.h"


template<class T>
File_text<T>::File_text(const std::string& name) : File(name)
{
    validate_text_file_extension(file_name);
}

template<class T>
File_text<T>::~File_text()
{
    Close_in();
    Close_out();
}

template<class T>
void File_text<T>::Open_file_in()
{
    if (file_i.is_open()) file_i.close();
    safe_open_for_read(file_i, file_name);
}

template<class T>
void File_text<T>::Open_file_out()
{
    if (file_o.is_open()) file_o.close();
    safe_open_for_write(file_o, file_name);
}

template<class T>
void File_text<T>::Close_in()
{
    if (file_i.is_open()) file_i.close();
}

template<class T>
void File_text<T>::Close_out()
{
    if (file_o.is_open()) file_o.close();
}

template<class T>
void File_text<T>::Write_string_line(const std::string& str)
{
    check_file_opened_for_write(file_o, file_name);
    file_o << str << std::endl;

    check_write_success(file_o, file_name, "строки");
}

template<class T>
void File_text<T>::Read_string_line(std::string& str)
{
    check_file_opened_for_read(file_i, file_name);
    check_not_end_of_file(file_i, file_name);

    std::getline(file_i, str);

    check_read_success(file_i, file_name, "строки");
}

template<class T>
void File_text<T>::Write_record_in_file_text(T& OBJECT)
{
    check_file_opened_for_write(file_o, file_name);

    const T& obj = OBJECT;
    file_o << obj;

    check_write_success(file_o, file_name, "объекта");
}

template<class T>
void File_text<T>::Read_record_in_file_text(T& OBJECT)
{
    check_file_opened_for_read(file_i, file_name);
    check_not_end_of_file(file_i, file_name);

    file_i >> OBJECT;
    check_read_success(file_i, file_name, "объекта");
}

// Реализации операторов
template<class T>
File_text<T>& File_text<T>::operator<<(T& obj)
{
    Write_record_in_file_text(obj);
    return *this;
}

template<class T>
File_text<T>& File_text<T>::operator>>(T& obj)
{
    Read_record_in_file_text(obj);
    return *this;
}

template<class T>
File_text<T>& File_text<T>::operator<<(const std::string& str)
{
    Write_string_line(str);
    return *this;
}

template<class T>
File_text<T>& File_text<T>::operator<<(const char* const str)
{
    check_file_opened_for_write(file_o, file_name);
    file_o << str;
    check_write_success(file_o, file_name, "C-строки");

    return *this;
}

template<class T>
File_text<T>& File_text<T>::operator>>(std::string& str)
{
    Read_string_line(str);
    return *this;
}


template class File_text<BookCard>;
template class File_text<ArticleCard>;
template class File_text<ArticleCollectionCard>;
template class File_text<IndependentPublicationCard>;