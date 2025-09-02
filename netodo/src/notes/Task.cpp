//
// Created by nekita on 01.09.25.
//

#include "netodo/notes/Task.hpp"

Task::Task(const std::string& name,
    const std::string& short_name, const std::string& description):
    Task(0, 0, name, short_name, description) {}

Task::Task(const int64_t parent_id, const int64_t id, const std::string& name,
    const std::string& short_name, const std::string& description,
    const int32_t progress_bar, const int32_t max_bar, const std::vector<int64_t>& todos,
    NoteStatus status): ToDo(parent_id, id, name, short_name, description, status),
                        progress_bar(progress_bar), max_bar(max_bar), todos(todos) {}

