#include "UserRepo.h"

void UserRepository::addUser(const User& user)
{
    users.push_back(user);
}

const std::vector<User>& UserRepository::getUsers() const
{
    return users;
}