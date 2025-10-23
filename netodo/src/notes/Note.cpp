//
// Created by nekita on 29.08.25.
//

#include "netodo/notes/Note.hpp"

Note::Note(const std::string& name, const std::string& description):
    Note(0, name, description) {
}

Note::Note(const int64_t id, const std::string& name,
           const std::string& description):
    id(id), name(name) {
    if (description.empty()) {
        this->description = "Description for Note " + name;
    } else {
        this->description = description;
    }
}
