//
// Created by nekita on 06.09.25.
//

#ifndef APP_HPP
#define APP_HPP

#include "netodo/db_manager/TaskDBManager.hpp"
#include "netodo/db_manager/ToDoDBManager.hpp"

class App {
public:
    App(ToDoDBManager& todo_db, TaskDBManager& task_db);

    [[nodiscard]] int64_t AddToDo(const ToDo& todo) const;
    [[nodiscard]] int64_t AddTask(const Task& task) const;
    void AddToDoToTask(const ToDo& todo, const Task& task) const;
    void UpdateToDo(int64_t id, const ToDo& todo) const;
    void UpdateTask(int64_t id, const Task& task) const;

    [[nodiscard]] std::vector<ToDo> GetAllToDo() const;
    [[nodiscard]] std::vector<Task> GetAllTask() const;
    [[nodiscard]] std::vector<ToDo> GetToDoByTask(const Task& task) const;
    [[nodiscard]] ToDo GetToDo(int64_t id) const;
    [[nodiscard]] Task GetTask(int64_t id) const;
private:
    ToDoDBManager todo_db_;
    TaskDBManager task_db_;

    void UpdateTaskByToDos(const Task& task) const;
};

#endif //APP_HPP
