//
// Created by nekita on 06.09.25.
//

#include "netodo/App.hpp"

App::App(ToDoDBManager& todo_db, TaskDBManager& task_db): todo_db_(std::move(todo_db)),
task_db_(std::move(task_db)) {}

int64_t App::AddToDo(const ToDo& todo) const {
    return todo_db_.AddToDo(todo);
}

int64_t App::AddTask(const Task& task) const {
    return task_db_.AddTask(task);
}

void App::UpdateToDo(int64_t id, const ToDo& todo) const {
    todo_db_.UpdateToDo(id, todo);
}

void App::UpdateTask(int64_t id, const Task& task) const {
    task_db_.UpdateTask(id, task);
}

void App::AddToDoToTask(const ToDo& todo, const Task& task) const {
    UpdateToDo(todo.id, ToDo(task.id, todo.id,
        todo.name, todo.description, todo.status));
}

std::vector<ToDo> App::GetAllToDo() const {
    return todo_db_.GetAllToDo();
}

std::vector<Task> App::GetAllTask() const {
    return task_db_.GetAllTask();
}

std::vector<ToDo> App::GetToDoByTask(const Task& task) const {
    return todo_db_.GetAllToDoByParent(task.id);
}

ToDo App::GetToDo(int64_t id) const {
    return todo_db_.GetToDo(id);
}

Task App::GetTask(int64_t id) const {
    return task_db_.GetTask(id);
}

