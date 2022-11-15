#include "name_error.h"

name_error::name_error()
{}

const char* name_error::what() const throw(){
    return "Name error.\nPlease, enter your full real name.";
}
