//
// Created by nekita on 29.08.25.
//

#include "netodo/notes/Note.hpp"

Note::Note(const std::string& name): name(name) {
    short_name = name.substr(0, 10);
    description = "Description for Note " + short_name;
}