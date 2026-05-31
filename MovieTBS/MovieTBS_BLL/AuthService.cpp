#include "AuthService.h"

AuthService::AuthService(UserRepository* repository)
{
    this->repository = repository;
}

bool AuthService::registerUser(
    const std::string& username,
    const std::string& password
)
{
    User user(username, password);

    repository->addUser(user);

    return true;
}

bool AuthService::login(
    const std::string& username,
    const std::string& password
)
{
    const std::vector<User>& users =
        repository->getUsers();

    for (const User& user : users)
    {
        if (user.getUsername() == username &&
            user.getPassword() == password)
        {
            return true;
        }
    }

    return false;
}