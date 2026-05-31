#include "User.h"

User::User()
{
}

User::User(
    const std::string& username,
    const std::string& password
)
{
    this->username = username;
    this->password = password;
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}