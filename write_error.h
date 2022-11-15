// Custom excetion class that helps to prevent problems
// with trials to text to email that does not exist
#ifndef WRITE_ERROR_H
#define WRITE_ERROR_H
#include <exception>
class write_error : public std::exception
{
public:
    write_error();

    virtual const char* what() const throw();
};

#endif // WRITE_ERROR_H
