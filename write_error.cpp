#include "write_error.h"

write_error::write_error()
{}

const char* write_error::what() const throw(){
    return "Email you've entered does not exist.";
}
