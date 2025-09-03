//
// Created by nekita on 02.09.25.
//

#include <map>

#include "netodo/db_manager/ToDoDBManager.hpp"

namespace {
    std::map<NoteStatus, std::string> status_to_text{{NoteStatus::NotStarted, "not started"},
                                                     {NoteStatus::InProgress, "in progress"},
                                                     {NoteStatus::Completed, "completed"}};

    std::map<std::string, NoteStatus> text_to_status{{"not started", NoteStatus::NotStarted},
                                                     {"in progress", NoteStatus::InProgress},
                                                     {"completed", NoteStatus::Completed}};
}

ToDoDBManager::ToDoDBManager(const std::string& db_path): db_(db_path,
    SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db_.exec("CREATE TABLE IF NOT EXISTS todo_table ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "parent_id INTEGER DEFAULT 0,"
            "name TEXT DEFAULT '',"
            "short_name TEXT DEFAULT '',"
            "description TEXT DEFAULT '',"
            "status TEXT DEFAULT 'not started');"
            );
}

int64_t ToDoDBManager::AddToDo(const ToDo& todo) const {
    SQLite::Statement query(db_, "INSERT INTO todo_table DEFAULT VALUES;");
    query.exec();
    int64_t new_id = db_.getLastInsertRowid();
    UpdateToDo(new_id, todo);
    return new_id;
}

ToDo ToDoDBManager::GetToDo(const int64_t id) const {
    SQLite::Statement query(db_, "SELECT * FROM todo_table "
                                 "WHERE id = ?");
    query.bind(1, id);
    return GetByQuery(query)[0];
}

std::vector<ToDo> ToDoDBManager::GetAllToDo() const {
    SQLite::Statement query(db_, "SELECT * FROM todo_table;");
    return GetByQuery(query);
}

std::vector<ToDo> ToDoDBManager::GetAllToDoByParent(const int64_t parent_id) const {
    SQLite::Statement query(db_, "SELECT * FROM todo_table "
                                 "WHERE parent_id = ?");
    query.bind(1, parent_id);
    return GetByQuery(query);
}

std::vector<ToDo> ToDoDBManager::GetByQuery(SQLite::Statement& query) {
    std::vector<ToDo> todos;
    while (query.executeStep()) {
        todos.emplace_back(query.getColumn(1).getInt64(), query.getColumn(0).getInt64(),
            query.getColumn(2).getString(), query.getColumn(3).getString(),
            query.getColumn(4).getString(), text_to_status[query.getColumn(5).getString()]);
    }

    return todos;
}

void ToDoDBManager::UpdateToDo(const int64_t id, const ToDo& todo) const {
    SQLite::Statement query(db_, "UPDATE todo_table "
             "SET parent_id = ?, name = ?, short_name = ?, description = ?, status = ?"
             "WHERE id = ?;");
    query.bind(1, todo.parent_id);
    query.bind(2, todo.name);
    query.bind(3, todo.short_name);
    query.bind(4, todo.description);
    query.bind(5, status_to_text[todo.status]);
    query.bind(6, id);
    query.exec();
}


void ToDoDBManager::Clear() {
    db_.exec("DELETE FROM todo_table");
}
