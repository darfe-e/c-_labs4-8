#ifndef INC_5_LAB_FILE_OPEN_EXCEPTION_H
#define INC_5_LAB_FILE_OPEN_EXCEPTION_H

#include "file_exception .h"

class file_open_exception : public file_exception
{
public:
    file_open_exception(const std::string& filename, int error_code = 100)
            : file_exception("Не удалось открыть файл: " + filename, error_code)
    {}
};

#endif //INC_5_LAB_FILE_OPEN_EXCEPTION_H
