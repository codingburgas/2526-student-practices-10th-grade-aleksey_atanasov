#pragma once

#pragma once

#include <vector>

#include "User.h"

class UserRepository
{
private:
    std::vector<User> users;

public:
    void addUser(const User& user);

    const std::vector<User>& getUsers() const;
};