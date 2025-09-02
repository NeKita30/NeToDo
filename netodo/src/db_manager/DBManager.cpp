//
// Created by nekita on 02.09.25.
//

#include "netodo/db_manager/DBManager.hpp"

DBManager::DBManager(const std::string& db_path):
    db_(db_path,
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db_.exec("CREATE TABLE IF NOT EXISTS note_table ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "short_name TEXT,"
            "description TEXT);"
            );
}

int64_t DBManager::AddNote(const Note& note) const {
    SQLite::Statement query(db_, "INSERT INTO note_table (name, short_name, description) "
                            "VALUES (?, ?, ?);");
    query.bind(1, note.name);
    query.bind(2, note.short_name);
    query.bind(3, note.description);
    query.exec();
    return db_.getLastInsertRowid();
}

Note DBManager::GetNote(int64_t id) const {
    SQLite::Statement query(db_, "SELECT * FROM note_table "
                            "WHERE id = ?;");
    query.bind(1, id);
    query.executeStep();
    Note note(query.getColumn(1).getString());
    note.short_name = query.getColumn(2).getString();
    note.description = query.getColumn(3).getString();
    return note;
}

std::vector<Note> DBManager::GetAllNotes() const {
    std::vector<Note> notes;
    SQLite::Statement query(db_, "SELECT * FROM note_table;");
    while (query.executeStep()) {
        notes.emplace_back(query.getColumn(1).getString());
        notes.back().short_name = query.getColumn(2).getString();
        notes.back().description = query.getColumn(3).getString();
    }
    return notes;
}

void DBManager::Clear() {
    db_.exec("DELETE FROM note_table;");
}
