#ifndef INC_5_LAB_FILE_WRITE_EXCEPTION_H
#define INC_5_LAB_FILE_WRITE_EXCEPTION_H

#include "file_exception .h"

class file_write_exception : public file_exception
{
public:
    file_write_exception(const std::string& filename, int error_code = 102)
            : file_exception("Ошибка записи в файл: " + filename, error_code)
    {}
};

#endif //INC_5_LAB_FILE_WRITE_EXCEPTION_H
