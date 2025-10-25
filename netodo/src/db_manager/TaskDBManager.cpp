//
// Created by nekita on 02.09.25.
//

#include "netodo/db_manager/TaskDBManager.hpp"

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

TaskDBManager::TaskDBManager(const std::string& db_path):
    db_(db_path,
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    try {
        db_.exec("CREATE TABLE IF NOT EXISTS task_table ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "parent_id INTEGER DEFAULT 0,"
                "name TEXT DEFAULT '',"
                "description TEXT DEFAULT '',"
                "status TEXT DEFAULT 'not started',"
                "progress INTEGER DEFAULT 0,"
                "max_progress INTEGER DEFAULT 0);");
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Error while create table `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(24)
                .Build<DBException>();
    }
}

int64_t TaskDBManager::AddTask(const Task& task) const {
    try {
        SQLite::Statement query(db_, "INSERT INTO task_table DEFAULT VALUES;");
        query.exec();
        int64_t new_id = db_.getLastInsertRowid();
        UpdateTask(new_id, task);
        return new_id;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage(
                        "SQLite error while insert default into `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(44)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage(
                        "Unknown error while insert default into `task_table`\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .Build<DBException>();
    }
}

Task TaskDBManager::GetTask(int64_t id) const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM task_table "
                                "WHERE id = ?;");
        query.bind(1, id);
        return GetByQuery(query)[0];
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while select by id from `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(69)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while select by id from `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .Build<DBException>();
    }
}

std::vector<Task> TaskDBManager::GetAllTask() const {
    try {
        SQLite::Statement query(db_, "SELECT * FROM task_table;");
        return GetByQuery(query);
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while select from `task_table:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(87)
                .Build<DBException>();
    }
}

std::vector<Task> TaskDBManager::GetByQuery(SQLite::Statement& query) {
    try {
        std::vector<Task> tasks;
        while (query.executeStep()) {
            tasks.emplace_back(query.getColumn(1).getInt64(), query.getColumn(0).getInt64(),
                               query.getColumn(2).getString(), query.getColumn(4).getString(),
                               query.getColumn(6).getInt(),
                               query.getColumn(7).getInt(), std::vector<int64_t>(),
                               text_to_status[query.getColumn(5).getString()]);
        }
        return tasks;
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while do query:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(100)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while do query:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .Build<DBException>();
    }
}

void TaskDBManager::UpdateTask(int64_t id, const Task& task) const {
    try {
        SQLite::Statement query(db_, "UPDATE task_table "
                                "SET parent_id = ?, name = ?,"
                                "description = ?, status = ?, progress = ?, max_progress = ? "
                                "WHERE id = ?;");
        query.bind(1, task.parent_id);
        query.bind(2, task.name);
        query.bind(3, task.description);
        query.bind(4, status_to_text[task.status]);
        query.bind(5, task.progress_bar);
        query.bind(6, task.max_bar);
        query.bind(7, id);
        query.exec();
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while update by id `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(135)
                .Build<DBException>();
    } catch (const std::exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("Unknown error while update by id `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .Build<DBException>();
    }
}


void TaskDBManager::Clear() {
    try {
        db_.exec("DELETE FROM task_table;");
    } catch (const SQLite::Exception& err) {
        ExceptionBuilder err_builder;
        throw err_builder.WithMessage("SQLite error while delete from `task_table`:\n" + std::string(err.what()))
                .InModule("TaskDBManager")
                .AtLine(153)
                .Build<DBException>();
    }
}
