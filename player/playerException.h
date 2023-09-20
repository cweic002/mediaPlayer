#ifndef PLAYER_EXCEPTION_H
#define PLAYER_EXCEPTION_H

#include <exception>
#include <string>

class PlayerException: public std::exception
{
public:
    PlayerException(const std::string & message);
    const char* what() const noexcept override ;
private:
    std::string message;
};

#endif // PLAYER_EXCEPTION_H
