#ifndef INC_5_LAB_INPUT_EXCEPTION_H
#define INC_5_LAB_INPUT_EXCEPTION_H

#include "my_exception.h"

class input_exception : public my_exception
{
public:
    input_exception(const std::string& message, int error_code)
            : my_exception(message, error_code)                                                             // Инициализация базового класса
    {}
};

#endif //INC_5_LAB_INPUT_EXCEPTION_H
