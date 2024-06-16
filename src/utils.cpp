#include "utils.hpp"

String maskPassword(String password)
{
    unsigned int len = password.length();
    String masked_password;
    masked_password.clear();
    for(unsigned int i = 0; i < len; i++)
    {
        masked_password += '*';
    }
    return masked_password;
}