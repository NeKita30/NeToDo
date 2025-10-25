//
// Created by nekita on 25.10.25.
//

#include "netodo/exceptions/CustomException.hpp"

CustomException::CustomException(const std::string& message):
    message_(message) {
}

const char* CustomException::what() const noexcept {
    return message_.c_str();
}

CustomException::~CustomException() noexcept = default;
