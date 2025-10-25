//
// Created by nekita on 02.09.25.
//

#include "netodo/db_manager/DBManager.hpp"
#include "netodo/exceptions/ExceptionBuilder.hpp"
#include "netodo/exceptions/Exceptions.hpp"

DBManager::DBManager(const std::string& db_path):
    db_(db_path,
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    try {
        db_.exec("CREATE TABLE IF NOT EXISTS note_table ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "description TEXT);"
                );
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("SQLite error while create table `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager")
                       .AtLine(13)
                       .Build<DBException>();
    }
}

int64_t DBManager::AddNote(const Note& note) const {
    try {
        SQLite::Statement query(db_, "INSERT INTO note_table (name, description) "
                                             "VALUES (?, ?);");
        query.bind(1, note.name);
        query.bind(2, note.description);
        query.exec();
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("SQLite error while insert into `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager")
                       .AtLine(33)
                       .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("Unknown error while insert into `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager").Build<DBException>();
    }
    return db_.getLastInsertRowid();
}

Note DBManager::GetNote(int64_t id) const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM note_table "
                                "WHERE id = ?;");
        query.bind(1, id);
        query.executeStep();
        Note note(query.getColumn(1).getString(),
                  query.getColumn(2).getString());
        return note;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("SQLite error while select by id from `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager")
                       .AtLine(54)
                       .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("Unknown error while select by id from `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager").Build<DBException>();
    }
}

std::vector<Note> DBManager::GetAllNotes() const {
    try {
        std::vector<Note> notes;
        SQLite::Statement query(db_, "SELECT * FROM note_table;");
        while (query.executeStep()) {
            notes.emplace_back(query.getColumn(1).getString(),
                               query.getColumn(2).getString());
        }
        return notes;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("SQLite error while select from `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager")
                       .AtLine(74)
                       .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("Unknown error while select from `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager").Build<DBException>();
    }
}

void DBManager::Clear() {
    try {
        db_.exec("DELETE FROM note_table;");
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder e_builder;
        throw e_builder.WithMessage("SQLite error while delete from `note_table`:\n" + std::string(err.what()))
                       .InModule("DBManager")
                       .AtLine(94)
                       .Build<DBException>();
    }
}
