//
// Created by nekita on 25.10.25.
//

#include "netodo/exceptions/Exceptions.hpp"

DBException::DBException(const std::string& message):
    CustomException(message) {}
