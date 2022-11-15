#include "login_error.h"

login_error::login_error()
{}

const char* login_error::what() const throw(){
    return "Log in error.\nWrong email or password.";
}
