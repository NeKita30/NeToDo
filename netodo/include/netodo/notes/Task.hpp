//
// Created by nekita on 01.09.25.
//

#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

#include "netodo/notes/ToDo.hpp"

struct Task: ToDo {
    int32_t progress_bar = 0;
    int32_t max_bar = 0;
    std::vector<int64_t> todos;

    explicit Task(const std::string& name, const std::string& short_name = "",
        const std::string& description = "");

    Task(int64_t parent_id, int64_t id, const std::string& name, const std::string& short_name = "",
        const std::string& description = "", int32_t progress_bar = 0, int32_t max_bar = 0,
        const std::vector<int64_t>& todos = {}, NoteStatus status = NoteStatus::NotStarted);
};

#endif //TASK_HPP
