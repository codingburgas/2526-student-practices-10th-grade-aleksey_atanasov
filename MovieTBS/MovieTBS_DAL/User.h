#pragma once

#include <string>

class User
{
private:
    std::string username;
    std::string password;

public:
    User();

    User(
        const std::string& username,
        const std::string& password
    );

    std::string getUsername() const;
    std::string getPassword() const;
};