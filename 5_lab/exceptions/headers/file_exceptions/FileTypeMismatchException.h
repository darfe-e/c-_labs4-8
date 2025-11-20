#ifndef INC_5_LAB_FILETYPEMISMATCHEXCEPTION_H
#define INC_5_LAB_FILETYPEMISMATCHEXCEPTION_H

#include "file_exception .h"

class FileTypeMismatchException : public file_exception
{
public:
    FileTypeMismatchException(const std::string& msg, int error_code) : file_exception(msg, error_code)
        {}
};

#endif //INC_5_LAB_FILETYPEMISMATCHEXCEPTION_H
