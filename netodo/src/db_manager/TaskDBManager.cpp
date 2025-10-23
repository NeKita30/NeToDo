//
// Created by nekita on 02.09.25.
//

#include "netodo/db_manager/TaskDBManager.hpp"

namespace {
    std::map<NoteStatus, std::string> status_to_text{{NoteStatus::NotStarted, "not started"},
                                                     {NoteStatus::InProgress, "in progress"},
                                                     {NoteStatus::Completed, "completed"}};

    std::map<std::string, NoteStatus> text_to_status{{"not started", NoteStatus::NotStarted},
                                                     {"in progress", NoteStatus::InProgress},
                                                     {"completed", NoteStatus::Completed}};
}

TaskDBManager::TaskDBManager(const std::string& db_path): db_(db_path,
    SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db_.exec("CREATE TABLE IF NOT EXISTS task_table ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "parent_id INTEGER DEFAULT 0,"
            "name TEXT DEFAULT '',"
            "short_name TEXT DEFAULT '',"
            "description TEXT DEFAULT '',"
            "status TEXT DEFAULT 'not started',"
            "progress INTEGER DEFAULT 0,"
            "max_progress INTEGER DEFAULT 0);");
}

int64_t TaskDBManager::AddTask(const Task& task) const {
    SQLite::Statement query(db_, "INSERT INTO task_table DEFAULT VALUES;");
    query.exec();
    int64_t new_id = db_.getLastInsertRowid();
    UpdateTask(new_id, task);
    return new_id;
}

Task TaskDBManager::GetTask(int64_t id) const {
    SQLite::Statement query(db_, "SELECT * FROM task_table "
                                 "WHERE id = ?;");
    query.bind(1, id);
    return GetByQuery(query)[0];
}

std::vector<Task> TaskDBManager::GetAllTask() const {
    SQLite::Statement query(db_, "SELECT * FROM task_table;");
    return GetByQuery(query);
}

std::vector<Task> TaskDBManager::GetByQuery(SQLite::Statement& query) {
    std::vector<Task> tasks;
    while (query.executeStep()) {
        tasks.emplace_back(query.getColumn(1).getInt64(), query.getColumn(0).getInt64(),
            query.getColumn(2).getString(), query.getColumn(3).getString(),
            query.getColumn(4).getString(), query.getColumn(6).getInt(),
            query.getColumn(7).getInt(), std::vector<int64_t>(),
            text_to_status[query.getColumn(5).getString()]);
    }
    return tasks;
}

void TaskDBManager::UpdateTask(int64_t id, const Task& task) const {
    SQLite::Statement query(db_, "UPDATE task_table "
                                 "SET parent_id = ?, name = ?, short_name = ?, "
                                 "description = ?, status = ?, progress = ?, max_progress = ? "
                                 "WHERE id = ?;");
    query.bind(1, task.parent_id);
    query.bind(2, task.name);
    query.bind(3, task.short_name);
    query.bind(4, task.description);
    query.bind(5, status_to_text[task.status]);
    query.bind(6, task.progress_bar);
    query.bind(7, task.max_bar);
    query.bind(8, id);
    query.exec();
}


void TaskDBManager::Clear() {
    db_.exec("DELETE FROM task_table;");
}




