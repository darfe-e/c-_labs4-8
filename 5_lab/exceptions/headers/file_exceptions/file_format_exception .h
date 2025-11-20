#ifndef INC_5_LAB_FILE_FORMAT_EXCEPTION_H
#define INC_5_LAB_FILE_FORMAT_EXCEPTION_H

#include "file_exception .h"

class file_format_exception : public file_exception
{
public:
    file_format_exception(const std::string& filename, int error_code = 103)
            : file_exception("Неверный формат файла: " + filename, error_code)
    {}
};

#endif //INC_5_LAB_FILE_FORMAT_EXCEPTION_H
