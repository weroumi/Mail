#include "emptyfield_error.h"

emptyfield_error::emptyfield_error()
{}

const char* emptyfield_error::what() const throw(){
    return "Empty field error.\nMake sure you've filled in all fields.";
}
