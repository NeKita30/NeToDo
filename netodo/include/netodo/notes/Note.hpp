//
// Created by nekita on 29.08.25.
//

#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>

struct Note {
    int64_t id;
    std::string name;
    std::string short_name;
    std::string description;

    explicit Note(const std::string& name, const std::string& short_name = "",
        const std::string& description = "");
    Note(int64_t id, const std::string& name,
        const std::string& short_name = "", const std::string& description = "");
};

enum class NoteStatus {
    NotStarted,
    InProgress,
    Completed
};


#endif // NOTE_HPP
