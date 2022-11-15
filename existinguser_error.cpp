#include "existinguser_error.h"

existinguser_error::existinguser_error()
{}

const char* existinguser_error::what() const throw(){
    return "Existing user error.\nUser with this email already exists.";
}
