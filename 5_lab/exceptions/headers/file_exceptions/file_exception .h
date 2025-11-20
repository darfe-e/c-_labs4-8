#ifndef INC_5_LAB_FILE_EXCEPTION_H
#define INC_5_LAB_FILE_EXCEPTION_H

#include "../input_exceptions/my_exception.h"

// Базовое исключение для файловых операций
class file_exception : public my_exception
{
public:
    file_exception(const std::string& message, int error_code)
            : my_exception("Файловая ошибка: " + message, error_code)
    {}
};

#endif //INC_5_LAB_FILE_EXCEPTION_H
