//
// Created by nekita on 25.10.25.
//

#ifndef EXCEPTIONBUILDER_HPP
#define EXCEPTIONBUILDER_HPP

#include <string>

#include "netodo/exceptions/CustomException.hpp"

class ExceptionBuilder {
public:
    ExceptionBuilder() = default;

    ExceptionBuilder& WithMessage(const std::string& message);
    ExceptionBuilder& InModule(const std::string& module);
    ExceptionBuilder& AtLine(size_t line);

    template <typename T=CustomException>
    requires std::derived_from<T, CustomException>
    T Build() const {
        std::string exception_message = message_;
        if (!module_.empty()) {
            exception_message += "\n"
                                 "In module: " + module_;
        }
        if (line_ > 0) {
            exception_message += "\n"
                                 "At line: " + std::to_string(line_);
        }
        return T(exception_message);
    }
private:
    size_t line_ = 0;
    std::string message_;
    std::string module_;
};

#endif //EXCEPTIONBUILDER_HPP
