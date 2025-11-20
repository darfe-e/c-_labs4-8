#ifndef INC_5_LAB_FILE_BINARY_H
#define INC_5_LAB_FILE_BINARY_H

#include "File.h"

template<class T>
class File_binary : public File
{
public:
    File_binary(const std::string& name);
    ~File_binary();

    void Remote();
    void Write_record_in_file(const T& OBJECT);
    void Read_record_in_file(T& OBJECT);
    bool R_end_file();
    void Open_for_read();

    // Перегруженные операторы для удобства
    File_binary<T>& operator<<(T& obj);
    File_binary<T>& operator>>(T& obj);
    File_binary<T>& operator<<(const int& val);
    File_binary<T>& operator>>(int& val);
};

#endif //INC_5_LAB_FILE_BINARY_H
