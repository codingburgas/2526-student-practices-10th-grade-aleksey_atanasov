#include "UserRepo.h"

void UserRepository::addUser(const User& user)
{
    users.push_back(user);
}

const std::vector<User>& UserRepository::getUsers() const
{
    return users;
}

bool UserRepository::userExists(
    const std::string& username
) const
{
    for (const User& user : users)
    {
        if (user.getUsername() == username)
        {
            return true;
        }
    }

    return false;
}