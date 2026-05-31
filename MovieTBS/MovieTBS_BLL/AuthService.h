#pragma once

#include "../MovieTBS_DAL/UserRepo.h"

class AuthService
{
private:
    UserRepository* repository;

public:
    AuthService(UserRepository* repository);

    bool registerUser(
        const std::string& username,
        const std::string& password
    );

    bool login(
        const std::string& username,
        const std::string& password
    );
};