//
// Created by nekita on 02.09.25.
//

#ifndef TODODBMANAGER_HPP
#define TODODBMANAGER_HPP

#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

#include "netodo/notes/ToDo.hpp"

class ToDoDBManager {
public:
    explicit ToDoDBManager(const std::string& db_path);

    [[nodiscard]] int64_t AddToDo(const ToDo& todo) const;
    [[nodiscard]] ToDo GetToDo(int64_t id) const;
    [[nodiscard]] std::vector<ToDo> GetAllToDo() const;
    [[nodiscard]] std::vector<ToDo> GetAllToDoByParent(int64_t parent_id) const;

    void UpdateToDo(int64_t id, const ToDo& todo) const;

    void Clear();
private:
    SQLite::Database db_;

    [[nodiscard]] static std::vector<ToDo> GetByQuery(SQLite::Statement& query);
};

#endif //TODODBMANAGER_HPP
