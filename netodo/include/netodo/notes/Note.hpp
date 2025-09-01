//
// Created by nekita on 29.08.25.
//

#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>

struct Note {
    std::string name;
    std::string short_name;
    std::string description;

    explicit Note(const std::string& name);
};


#endif // NOTE_HPP
