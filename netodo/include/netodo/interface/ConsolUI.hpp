//
// Created by nekita on 03.09.25.
//

#ifndef CONSOLUI_HPP
#define CONSOLUI_HPP

#include <istream>
#include <ostream>
#include <netodo/App.hpp>

#include "netodo/interface/IUI.hpp"

class ConsolUI : public IUI {
public:
    ConsolUI(std::istream& is, std::ostream& os, App& app);
    ~ConsolUI() override = default;

    void Show() override;
    void ShowToDos(const std::vector<ToDo>& todos) override;
    void ShowTasks(const std::vector<Task>& tasks) override;
    void InputToDo() override;
    void InputTask() override;
    void EditToDo(ToDo& todo) override;
    void EditTask(Task& task) override;
private:
    void ProcessRequest();

    std::istream& is_;
    std::ostream& os_;
    App& app_;
};

#endif //CONSOLUI_HPP
