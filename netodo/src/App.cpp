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
    ToDo prev_todo = GetToDo(id);
    todo_db_.UpdateToDo(id, todo);
    if (todo.HasParent()) {
        Task task = GetTask(todo.parent_id);
        UpdateTaskByToDos(task);
    }
}

void App::UpdateTaskByToDos(const Task& task) const {
    std::vector<ToDo> children = GetToDosByTask(task);
    auto new_max_bar = static_cast<int32_t>(children.size());
    int32_t new_progress = 0;
    NoteStatus new_status = task.status;
    for (const auto& child : children) {
        if (child.status == NoteStatus::Completed) {
            ++new_progress;
        } else if (child.status == NoteStatus::InProgress) {
            new_status = NoteStatus::InProgress;
        }
    }
    if (new_progress == new_max_bar) {
        new_status = NoteStatus::Completed;
    }
    Task updated_task = task;
    updated_task.status = new_status;
    updated_task.max_bar = new_max_bar;
    updated_task.progress_bar = new_progress;
    UpdateTask(task.id, updated_task);
}


void App::UpdateTask(int64_t id, const Task& task) const {
    task_db_.UpdateTask(id, task);
}

void App::AddToDoToTask(const ToDo& todo, const Task& task) const {
    todo_db_.UpdateToDo(todo.id, ToDo(task.id, todo.id,
        todo.name, todo.description, todo.status));
    UpdateTaskByToDos(task);
}

std::vector<ToDo> App::GetAllToDo() const {
    return todo_db_.GetAllToDo();
}

std::vector<Task> App::GetAllTask() const {
    return task_db_.GetAllTask();
}

std::vector<ToDo> App::GetToDosByTask(const Task& task) const {
    return todo_db_.GetAllToDoByParent(task.id);
}

ToDo App::GetToDo(int64_t id) const {
    return todo_db_.GetToDo(id);
}

Task App::GetTask(int64_t id) const {
    return task_db_.GetTask(id);
}

std::optional<Task> App::GetTaskByTodo(const ToDo& todo) const {
    if (!todo.HasParent()) {
        return std::nullopt;
    }
    return GetTask(todo.parent_id);
}

