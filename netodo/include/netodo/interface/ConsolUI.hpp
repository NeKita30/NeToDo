//
// Created by nekita on 03.09.25.
//

#ifndef CONSOLUI_HPP
#define CONSOLUI_HPP

#include <istream>
#include <ostream>
#include <netodo/App.hpp>

#include "netodo/interface/IUI.hpp"

class ConsolUI: public IUI {
public:
    ConsolUI(std::istream& is, std::ostream& os, App& app);
    ~ConsolUI() override = default;

    void Show() override;
    void ShowToDos(const std::vector<ToDo>& todos) override;
    void ShowTasks(const std::vector<Task>& tasks) override;
    void ShowToDo(const ToDo& todo) override;
    void ShowTask(const Task& task) override;
    int64_t InputToDo() override;
    int64_t InputTask() override;
    void EditToDo(const ToDo& todo) override;
    void EditTask(const Task& task) override;
private:
    void ProcessRequest();

    void ShowToDoCommands(const ToDo& todo);
    void ProcessToDoRequest(const ToDo& todo);
    void ShowTaskCommands(const Task& task);
    void ProcessTaskRequest(const Task& task);
    void ShowTaskToDos(const Task& task);
    static std::string StatusToText(NoteStatus status);

    std::istream& is_;
    std::ostream& os_;
    App& app_;
};

#endif //CONSOLUI_HPP
