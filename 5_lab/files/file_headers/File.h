#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\headers/IndependentPublicationCard.h"
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\headers/BookCard.h"
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\headers/ArticleCard.h"
#include "D:\study\2_year\pnaiavy\c-_labs4-8\5_lab\headers/ArticleCollectionCard.h"

class File
{
protected:
    std::string file_name;    // Имя файла
    std::ifstream file_i;     // Поток для чтения
    std::ofstream file_o;     // Поток для записи
    std::fstream file_stream; // Поток для чтения/записи

public:
    File(const std::string& name) : file_name(name) {}
    virtual ~File() {}
};



#endif
