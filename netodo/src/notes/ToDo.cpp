//
// Created by nekita on 01.09.25.
//

#include "netodo/notes/ToDo.hpp"

ToDo::ToDo(const std::string& name,
           const std::string& description, NoteStatus status):
    ToDo(0, 0, name, description, status) {
}

ToDo::ToDo(const int64_t parent_id, const int64_t id, const std::string& name,
           const std::string& description, NoteStatus status):
    Note(id, name,
         description),
    parent_id(parent_id),
    status(status) {
}

bool ToDo::HasParent() const {
    return parent_id != 0;
}