//
// Created by nekita on 25.10.25.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "netodo/exceptions/CustomException.hpp"

class DBException: public CustomException {
public:
    explicit DBException(const std::string& message);
};

#endif //EXCEPTIONS_HPP
