#ifndef FILE_TEXT_H
#define FILE_TEXT_H

#include "File.h"
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\exceptions/func_with_exc.h"
#include <iostream>
#include <fstream>
#include <string>

template<class T>
class File_text : public File
{
private:
    std::ifstream file_i;
    std::ofstream file_o;

public:
    File_text(const std::string& name);
    ~File_text();

    // Основные методы с выбрасыванием исключений
    void Open_file_in();
    void Open_file_out();
    void Close_in();
    void Close_out();

    // Чтение/запись с исключениями
    void Write_string_line(const std::string& str);
    void Read_string_line(std::string& str);
    void Write_record_in_file_text(T& OBJECT);
    void Read_record_in_file_text(T& OBJECT);

    // Операторы
    File_text<T>& operator<<(T& obj);
    File_text<T>& operator>>(T& obj);
    File_text<T>& operator<<(const std::string& str);
    File_text<T>& operator<<(const char* const str);
    File_text<T>& operator>>(std::string& str);
};

#endif // FILE_TEXT_H