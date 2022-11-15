#include "custom_exception.h"

newline_error::newline_error()
{}

const char* newline_error::what() const throw(){
    return "Make sure your message doesn't contain \"\\n\" or \";\".";
}
