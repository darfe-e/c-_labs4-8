#ifndef INC_5_LAB_FILE_ACCESS_EXCEPTION_H
#define INC_5_LAB_FILE_ACCESS_EXCEPTION_H

#include "file_exception .h"

class file_access_exception : public file_exception
{
public:
    file_access_exception(const std::string& filename, int error_code = 104)
            : file_exception("Ошибка доступа к файлу: " + filename, error_code)
    {}
};

#endif //INC_5_LAB_FILE_ACCESS_EXCEPTION_H
