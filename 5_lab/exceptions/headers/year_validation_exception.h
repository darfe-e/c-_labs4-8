#ifndef INC_5_LAB_YEAR_VALIDATION_EXCEPTION_H
#define INC_5_LAB_YEAR_VALIDATION_EXCEPTION_H

#include "input_exception.h"

class year_validation_exception : public input_exception
{
public:
    year_validation_exception(const std::string& message, int error_code)
            : input_exception(message, error_code)                                                          // Инициализация базового класса
    {}
};

#endif //INC_5_LAB_YEAR_VALIDATION_EXCEPTION_H
