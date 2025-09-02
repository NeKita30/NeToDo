//
// Created by nekita on 29.08.25.
//

#include "netodo/notes/Note.hpp"

Note::Note(const std::string& name, const std::string& short_name,
    const std::string& description): Note(0, name, short_name, description) {}

Note::Note(const int64_t id, const std::string& name, const std::string& short_name,
    const std::string& description): id(id), name(name) {
    if (short_name.empty()) {
        this->short_name = name.substr(0, 10);
    } else {
        this->short_name = short_name;
    }
    if (description.empty()) {
        this->description = "Description for Note " + name;
    } else {
        this->description = description;
    }
}