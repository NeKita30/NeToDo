//
// Created by nekita on 25.10.25.
//

#include "netodo/exceptions/ExceptionBuilder.hpp"

ExceptionBuilder& ExceptionBuilder::WithMessage(const std::string& message) {
    message_ = message;
    return *this;
}

ExceptionBuilder& ExceptionBuilder::InModule(const std::string& module) {
    module_ = module;
    return *this;
}

ExceptionBuilder& ExceptionBuilder::AtLine(size_t line) {
    line_ = line;
    return *this;
}
