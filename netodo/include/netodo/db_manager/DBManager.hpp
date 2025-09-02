//
// Created by nekita on 02.09.25.
//

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

#include "netodo/notes/Note.hpp"

class DBManager {
public:
    explicit DBManager(const std::string& db_path);

    [[nodiscard]] int64_t AddNote(const Note& note) const;

    [[nodiscard]] Note GetNote(int64_t id) const;

    [[nodiscard]] std::vector<Note> GetAllNotes() const;

    void Clear();

private:
    SQLite::Database db_;
};

#endif //DBMANAGER_HPP
