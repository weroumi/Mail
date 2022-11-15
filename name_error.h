// Custom exception class that prevents
// entering entering unreal name
#ifndef NAME_ERROR_H
#define NAME_ERROR_H
#include <exception>
class name_error : public std::exception
{
public:
    name_error();

    virtual const char* what() const throw();
};

#endif // NAME_ERROR_H
