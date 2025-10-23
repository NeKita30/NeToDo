//
// Created by nekita on 02.09.25.
//

#ifndef TASKDBMANAGER_HPP
#define TASKDBMANAGER_HPP

#include "netodo/notes/Task.hpp"
#include "netodo/db_manager/DBManager.hpp"

class TaskDBManager {
public:
    explicit TaskDBManager(const std::string& db_path);

    [[nodiscard]] int64_t AddTask(const Task& task) const;
    [[nodiscard]] Task GetTask(int64_t id) const;
    [[nodiscard]] std::vector<Task> GetAllTask() const;

    void UpdateTask(int64_t id, const Task& task) const;

    void Clear();
private:
    SQLite::Database db_;

    [[nodiscard]] static std::vector<Task> GetByQuery(SQLite::Statement& query);
};

#endif //TASKDBMANAGER_HPP
