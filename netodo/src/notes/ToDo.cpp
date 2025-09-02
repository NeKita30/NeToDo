//
// Created by nekita on 01.09.25.
//

#include "netodo/notes/ToDo.hpp"

ToDo::ToDo(const std::string& name, const std::string& short_name,
    const std::string& description, NoteStatus status): ToDo(0, 0, name, short_name, description, status) {}

ToDo::ToDo(const int64_t parent_id, const int64_t id, const std::string& name,
    const std::string& short_name, const std::string& description, NoteStatus status): Note(id, name, short_name,
                                                                                            description),
                                                                                       parent_id(parent_id),
                                                                                       status(status) {}
