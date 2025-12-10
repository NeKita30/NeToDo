//
// Created by nekita on 03.09.25.
//

#include "netodo/interface/ConsolUI.hpp"

#include <iostream>

ConsolUI::ConsolUI(std::istream& is, std::ostream& os, App& app):
    is_(is), os_(os), app_(app) {
}

void ConsolUI::Show() {
    os_ << "Commands:" << std::endl;
    os_ << "1 - Create Task" << std::endl;
    os_ << "2 - Create ToDo" << std::endl;
    os_ << "3 - Show all Tasks" << std::endl;
    os_ << "4 - Show all ToDos" << std::endl;
    os_ << "5 - Show ToDo" << std::endl;
    os_ << "6 - Show Task" << std::endl;
    os_ << "Q - Quit" << std::endl;
    ProcessRequest();
}

void ConsolUI::ProcessRequest() {
    std::string command;
    is_ >> command;
    if (command == "1") {
        InputTask();
    } else if (command == "2") {
        InputToDo();
    } else if (command == "3") {
        ShowTasks(app_.GetAllTask());
    } else if (command == "4") {
        ShowToDos(app_.GetAllToDo());
    } else if (command == "5") {
        os_ << "ToDo id: ";
        int64_t id;
        is_ >> id;
        ShowToDo(app_.GetToDo(id));
    } else if (command == "6") {
        os_ << "Task id: ";
        int64_t id;
        is_ >> id;
        ShowTask(app_.GetTask(id));
    } else if (command == "Q") {
        return;
    } else {
        os_ << "Wrong command: " << command << std::endl;
    }
    Show();
}


int64_t ConsolUI::InputToDo() {
    os_ << "ToDo name:" << std::endl;
    std::string name;
    is_ >> std::ws;
    std::getline(is_, name);

    os_ << "ToDo description:" << std::endl;
    std::string description;
    is_ >> std::ws;
    std::getline(is_, description);
    int64_t id = app_.AddToDo(ToDo(name, description));
    os_ << "Add ToDo, id: " << id << std::endl;
    return id;
}

void ConsolUI::EditToDo(const ToDo& todo) {
    os_ << "ToDo current name: " << todo.name << std::endl;
    os_ << "ToDo new name: ";
    std::string name;
    is_ >> std::ws;
    std::getline(is_, name);

    os_ << "ToDo current description: " << todo.description << std::endl;
    os_ << "ToDo new description: ";
    std::string description;
    is_ >> std::ws;
    std::getline(is_, description);

    ToDo updated_todo(todo);
    updated_todo.name = name;
    updated_todo.description = description;
    app_.UpdateToDo(todo.id, updated_todo);
}

void ConsolUI::ShowToDos(const std::vector<ToDo>& todos) {
    os_ << "-----------------------" << std::endl;
    for (auto& todo: todos) {
        os_ << "ToDo id: " << todo.id << ", name: " << todo.name << std::endl;
        os_ << StatusToText(todo.status) << std::endl;
        os_ << "-----------------------" << std::endl;
    }
}

void ConsolUI::ShowToDo(const ToDo& todo) {
    os_ << "-----------------------" << std::endl;
    os_ << "ToDo id: " << todo.id << std::endl;
    os_ << "Name: " << todo.name << std::endl;
    auto task_of_todo = app_.GetTaskByTodo(todo);
    if (task_of_todo.has_value()) {
        os_ << "From Task " << task_of_todo->name << ", id: " << task_of_todo->id << std::endl;
    }
    os_ << StatusToText(todo.status) << std::endl;
    os_ << todo.description << std::endl;
    os_ << "-----------------------" << std::endl;

    ShowToDoCommands(todo);
}

void ConsolUI::ShowToDoCommands(const ToDo& todo) {
    os_ << "Commands:" << std::endl;
    os_ << "1 - Edit ToDo name and description" << std::endl;
    os_ << "2 - Add ToDo to Task by id" << std::endl;
    switch (todo.status) {
        case NoteStatus::NotStarted:
            os_ << "3 - Start ToDo" << std::endl;
            break;
        case NoteStatus::InProgress:
            os_ << "3 - Completed ToDo" << std::endl;
            break;
        case NoteStatus::Completed:
            os_ << "3 - Restart ToDo" << std::endl;
    }
    os_ << "Q - Go back home" << std::endl;

    ProcessToDoRequest(todo);
}

void ConsolUI::ProcessToDoRequest(const ToDo& todo) {
    std::string command;
    is_ >> command;
    if (command == "1") {
        EditToDo(todo);
    } else if (command == "2") {
        os_ << "Task id: ";
        int64_t task_id;
        is_ >> task_id;
        app_.AddToDoToTask(todo, app_.GetTask(task_id));
    } else if (command == "3") {
        auto new_status = NoteStatus::NotStarted;
        switch (todo.status) {
            case NoteStatus::NotStarted:
                new_status = NoteStatus::InProgress;
                break;
            case NoteStatus::InProgress:
                new_status = NoteStatus::Completed;
                break;
            case NoteStatus::Completed:
                new_status = NoteStatus::InProgress;
        }
        ToDo updated_todo(todo);
        updated_todo.status = new_status;
        app_.UpdateToDo(todo.id, updated_todo);
    } else if (command == "Q") {
        return;
    } else {
        os_ << "Wrong command: " << command << std::endl;
    }
    ToDo updated_todo = app_.GetToDo(todo.id);
    ShowToDo(updated_todo);
}


int64_t ConsolUI::InputTask() {
    os_ << "Task name:" << std::endl;
    std::string name;
    is_ >> std::ws;
    std::getline(is_, name);

    os_ << "Task description:" << std::endl;
    std::string description;
    is_ >> std::ws;
    std::getline(is_, description);

    int64_t task_id = app_.AddTask(Task(name, description));
    Task task = app_.GetTask(task_id);
    os_ << "Task's ToDos number" << std::endl;
    int todo_number;
    is_ >> todo_number;
    os_ << "Task's ToDos ids:" << std::endl;
    for (int i = 0; i < todo_number; i++) {
        int64_t todo_id;
        is_ >> todo_id;
        app_.AddToDoToTask(app_.GetToDo(todo_id), task);
    }
    os_ << "Add Task, id: " << task_id << std::endl;
    return task_id;
}

void ConsolUI::EditTask(const Task& task) {
    os_ << "Task current name: " << task.name << std::endl;
    os_ << "Task new name: ";
    std::string name;
    is_ >> std::ws;
    std::getline(is_, name);

    os_ << "Task current description: " << task.description << std::endl;
    os_ << "Task new description: ";
    std::string description;
    is_ >> std::ws;
    std::getline(is_, description);

    Task updated_task(task);
    updated_task.name = name;
    updated_task.description = description;
    app_.UpdateTask(task.id, updated_task);
}

void ConsolUI::ShowTasks(const std::vector<Task>& tasks) {
    os_ << "-----------------------" << std::endl;
    for (auto& task: tasks) {
        std::string status = StatusToText(task.status);
        os_ << "Task id: " << task.id << ", name: " << task.name << std::endl;
        os_ << status << std::endl;
        os_ << "-----------------------" << std::endl;
    }
}

void ConsolUI::ShowTask(const Task& task) {
    os_ << "-----------------------" << std::endl;
    os_ << "Task id: " << task.id << std::endl;
    os_ << "Name: " << task.name << std::endl;
    os_ << StatusToText(task.status) << std::endl;
    os_ << "Progress: " << task.progress_bar << " of " << task.max_bar << std::endl;
    os_ << task.description << std::endl;
    os_ << "-----------------------" << std::endl;

    ShowTaskCommands(task);
}

void ConsolUI::ShowTaskCommands(const Task& task) {
    os_ << "Commands:" << std::endl;
    os_ << "1 - Edit Task name and description" << std::endl;
    os_ << "2 - Show Task's ToDos" << std::endl;
    os_ << "3 - Add ToDo to Task by id" << std::endl;
    os_ << "4 - Create ToDo in this Task" << std::endl;
    os_ << "Q - Go back home" << std::endl;

    ProcessTaskRequest(task);
}

void ConsolUI::ProcessTaskRequest(const Task& task) {
    std::string command;
    is_ >> command;
    if (command == "1") {
        EditTask(task);
    } else if (command == "2") {
        ShowTaskToDos(task);
    } else if (command == "3") {
        os_ << "ToDo id: ";
        int64_t todo_id;
        is_ >> todo_id;
        app_.AddToDoToTask(app_.GetToDo(todo_id), task);
    } else if (command == "4") {
        int64_t todo_id = InputToDo();
        app_.AddToDoToTask(app_.GetToDo(todo_id), task);
    } else if (command == "Q") {
        return;
    } else {
        os_ << "Wrong command: " << command << std::endl;
    }
    Task updated_task = app_.GetTask(task.id);
    ShowTask(updated_task);
}

void ConsolUI::ShowTaskToDos(const Task& task) {
    std::vector<ToDo> todos = app_.GetToDosByTask(task);
    ShowToDos(todos);
}


std::string ConsolUI::StatusToText(NoteStatus status) {
    switch (status) {
        case NoteStatus::NotStarted:
            return "not started";
        case NoteStatus::InProgress:
            return "started";
        case NoteStatus::Completed:
            return "completed";
    }
    return "";
}
