// Custom exception class to prevent entering "\n" in message text
// so that it could be successfully and safely written to .csv file

#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H
#include <exception>
class newline_error : public std::exception
{
public:
    newline_error();

    virtual const char* what() const throw();
};

#endif // CUSTOM_EXCEPTION_H
