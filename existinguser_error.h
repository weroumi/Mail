// Custom exception class to prevent creating
// acount with login that already exists
#ifndef EXISTINGUSER_ERROR_H
#define EXISTINGUSER_ERROR_H
#include <exception>
class existinguser_error : public std::exception
{
public:
    existinguser_error();

    virtual const char* what() const throw();
};

#endif // EXISTINGUSER_ERROR_H
