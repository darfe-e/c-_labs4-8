#ifndef INC_5_LAB_FILE_READ_EXCEPTION_H
#define INC_5_LAB_FILE_READ_EXCEPTION_H

#include "file_exception .h"

class file_read_exception : public file_exception
{
public:
    file_read_exception(const std::string& filename, int error_code = 101)
            : file_exception("Ошибка чтения файла: " + filename, error_code)
    {}
};

#endif //INC_5_LAB_FILE_READ_EXCEPTION_H
