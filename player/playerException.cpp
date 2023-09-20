#include "playerException.h"

PlayerException::PlayerException(const std::string & message):message{message}{

}

const char * PlayerException::what() const noexcept {
    return message.c_str();
}
