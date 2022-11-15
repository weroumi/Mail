// Custom exception class to prevent
// loggin into acount that does not exist
#ifndef LOGIN_ERROR_H
#define LOGIN_ERROR_H
#include <exception>
class login_error : public std::exception
{
public:
    login_error();

    virtual const char* what() const throw();
};

#endif // LOGIN_ERROR_H
