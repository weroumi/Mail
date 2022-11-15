// Custom exception class to prevent problems with empty field
#ifndef EMPTYFIELD_ERROR_H
#define EMPTYFIELD_ERROR_H
#include <exception>
class emptyfield_error : public std::exception
{
public:
    emptyfield_error();

    virtual const char* what() const throw();
};

#endif // EMPTYFIELD_ERROR_H
