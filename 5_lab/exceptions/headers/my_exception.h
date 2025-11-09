#ifndef INC_5_LAB_MY_EXCEPTION_H
#define INC_5_LAB_MY_EXCEPTION_H

#include <iostream>

class my_exception : public std::runtime_error
{
private:
    int error_code_;
public:
    my_exception(const std::string& message, int error_code)
            : std::runtime_error(message), error_code_(error_code)                                          // Инициализация базового класса и кода ошибки
    {}

    int get_error_code() const { return error_code_; }                                                  // Геттер для кода ошибки
};

#endif //INC_5_LAB_MY_EXCEPTION_H
