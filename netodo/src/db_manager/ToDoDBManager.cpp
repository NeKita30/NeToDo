//
// Created by nekita on 02.09.25.
//

#include <map>

#include "netodo/db_manager/ToDoDBManager.hpp"

#include <netodo/exceptions/ExceptionBuilder.hpp>
#include <netodo/exceptions/Exceptions.hpp>

namespace {
    std::map<NoteStatus, std::string> status_to_text{{NoteStatus::NotStarted, "not started"},
                                                     {NoteStatus::InProgress, "in progress"},
                                                     {NoteStatus::Completed, "completed"}};

    std::map<std::string, NoteStatus> text_to_status{{"not started", NoteStatus::NotStarted},
                                                     {"in progress", NoteStatus::InProgress},
                                                     {"completed", NoteStatus::Completed}};
}

ToDoDBManager::ToDoDBManager(const std::string& db_path):
    db_(db_path,
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    try {
        db_.exec("CREATE TABLE IF NOT EXISTS todo_table ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "parent_id INTEGER DEFAULT 0,"
                "name TEXT DEFAULT '',"
                "description TEXT DEFAULT '',"
                "status TEXT DEFAULT 'not started');"
                );
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while create `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(25)
                .Build<DBException>();
    }
}

int64_t ToDoDBManager::AddToDo(const ToDo& todo) const {
    try {
        SQLite::Statement query(db_, "INSERT INTO todo_table DEFAULT VALUES;");
        query.exec();
        int64_t new_id = db_.getLastInsertRowid();
        UpdateToDo(new_id, todo);
        return new_id;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage(
                        "SQLite error while insert default into `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(45)
                .Build<DBException>();
    } catch (const DBException& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("DB error while insert into `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}

ToDo ToDoDBManager::GetToDo(const int64_t id) const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM todo_table "
                                "WHERE id = ?");
        query.bind(1, id);
        return GetByQuery(query)[0];
    } catch (const DBException& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("DB error while select by id from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(69)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while select by id from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}

std::vector<ToDo> ToDoDBManager::GetAllToDo() const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM todo_table;");
        return GetByQuery(query);
    } catch (const DBException& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("DB error while select from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(87)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while select from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}

std::vector<ToDo> ToDoDBManager::GetAllToDoByParent(const int64_t parent_id) const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM todo_table "
                                "WHERE parent_id = ?");
        query.bind(1, parent_id);
        return GetByQuery(query);
    } catch (const DBException& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("DB error while select by parent from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(107)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage(
                        "Unknown error while select by parent from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}

std::vector<ToDo> ToDoDBManager::GetByQuery(SQLite::Statement& query) {
    try {
        std::vector<ToDo> todos;
        while (query.executeStep()) {
            todos.emplace_back(query.getColumn(1).getInt64(), query.getColumn(0).getInt64(),
                               query.getColumn(2).getString(), query.getColumn(3).getString(),
                               text_to_status[query.getColumn(4).getString()]);
        }

        return todos;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while do query:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(126)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while do query:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}

void ToDoDBManager::UpdateToDo(const int64_t id, const ToDo& todo) const {
    try {
        SQLite::Statement query(db_, "UPDATE todo_table "
                                "SET parent_id = ?, name = ?, description = ?, status = ?"
                                "WHERE id = ?;");
        query.bind(1, todo.parent_id);
        query.bind(2, todo.name);
        query.bind(3, todo.description);
        query.bind(4, status_to_text[todo.status]);
        query.bind(5, id);
        query.exec();
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while update `todo_table` by id:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(157)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while update `todo_table` by id:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .Build<DBException>();
    }
}


void ToDoDBManager::Clear() {
    try {
        db_.exec("DELETE FROM todo_table");
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while delete from `todo_table`:\n" + std::string(err.what()))
                .InModule("ToDoDBManager")
                .AtLine(175)
                .Build<DBException>();
    }
}
