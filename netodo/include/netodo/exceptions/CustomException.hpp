//
// Created by nekita on 25.10.25.
//

#ifndef CUSTOMEXCEPTION_HPP
#define CUSTOMEXCEPTION_HPP

#include <exception>
#include <string>

class CustomException : public std::exception {
public:
    explicit CustomException(const std::string& message);

    [[nodiscard]] const char* what() const noexcept override;

    ~CustomException() noexcept override;

private:
    std::string message_;
};


#endif //CUSTOMEXCEPTION_HPP
