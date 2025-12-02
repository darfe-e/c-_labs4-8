#ifndef INC_5_LAB_FILE_BINARY_H
#define INC_5_LAB_FILE_BINARY_H

#include "File.h"
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\exceptions/func_with_exc.h"
#include <iostream>
#include <fstream>
#include <string>

template<class T>
class File_binary : public File
{
private:
    std::fstream file_stream;

public:
    File_binary(const std::string& name);
    ~File_binary();

    void Open_for_read();
    void Open_for_write();
    void Close();
    void Clear_file();

    void Write_record_in_file(const T& OBJECT);
    void Read_record_in_file(T& OBJECT);

    // Операторы для удобства
    File_binary<T>& operator<<(const T& obj);
    File_binary<T>& operator>>(T& obj);
    File_binary<T>& operator<<(int val);
    File_binary<T>& operator>>(int& val);
};

#endif //INC_5_LAB_FILE_BINARY_H