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
    } else if (command == "Q") {
        return;
    } else {
        os_ << "Wrong command!" << std::endl;
    }
    Show();
}


void ConsolUI::InputToDo() {
    os_ << "ToDo name:" << std::endl;
    std::string name;
    is_ >> name;

    os_ << "ToDo description:" << std::endl;
    std::string description;
    is_ >> description;
    int64_t id = app_.AddToDo(ToDo(name, description));
    os_ << "Add ToDo, id: " << id << std::endl;
}

void ConsolUI::EditToDo(ToDo& todo) {
}

void ConsolUI::ShowToDos(const std::vector<ToDo>& todos) {
    for (auto& todo: todos) {
        std::string status;
        switch (todo.status) {
            case NoteStatus::NotStarted:
                status = "not started";
                break;
            case NoteStatus::InProgress:
                status = "started";
                break;
            case NoteStatus::Completed:
                status = "completed";
        }
        os_ << "ToDo id: " << todo.id  <<", name: " << todo.name << std::endl;
        os_ << status << std::endl;
        os_ << "-----------------------" << std::endl;
    }
}

void ConsolUI::InputTask() {
    os_ << "Task name:" << std::endl;
    std::string name;
    is_ >> name;

    os_ << "Task description:" << std::endl;
    std::string description;
    is_ >> description;

    int64_t task_id = app_.AddTask(Task(name, description));
    Task task = app_.GetTask(task_id);
    os_ << "Task's ToDos number" << std::endl;
    int todo_number;
    std::cin >> todo_number;
    os_ << "Task's ToDos ids:" << std::endl;
    for (int i = 0; i < todo_number; i++) {
        int64_t todo_id;
        std::cin >> todo_id;
        app_.AddToDoToTask(app_.GetToDo(todo_id), task);
    }
}

void ConsolUI::EditTask(Task& task) {

}

void ConsolUI::ShowTasks(const std::vector<Task>& tasks) {
    for (auto& task: tasks) {
        std::string status;
        switch (task.status) {
            case NoteStatus::NotStarted:
                status = "not started";
            break;
            case NoteStatus::InProgress:
                status = "started";
            break;
            case NoteStatus::Completed:
                status = "completed";
        }
        os_ << "Task id: " << task.id  <<", name: " << task.name << std::endl;
        os_ << status << std::endl;
        os_ << "-----------------------" << std::endl;
    }
}
