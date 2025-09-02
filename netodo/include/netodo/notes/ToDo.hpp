//
// Created by nekita on 01.09.25.
//

#ifndef TODO_HPP
#define TODO_HPP

#include "netodo/notes/Note.hpp"

struct ToDo: Note {
    int64_t parent_id;
    NoteStatus status = NoteStatus::NotStarted;

    explicit ToDo(const std::string& name,
        const std::string& short_name = "", const std::string& description = "",
        NoteStatus status = NoteStatus::NotStarted);
    ToDo(int64_t parent_id, int64_t id, const std::string& name,
        const std::string& short_name = "", const std::string& description = "",
        NoteStatus status = NoteStatus::NotStarted);
};

#endif //TODO_HPP
