//
// Created by nekita on 03.09.25.
//

#ifndef IUI_HPP
#define IUI_HPP

#include <vector>

#include "netodo/notes/Task.hpp"
#include "netodo/notes/ToDo.hpp"

class IUI {
public:
    virtual ~IUI() = default;
    virtual void Show() = 0;
    virtual void ShowToDos(const std::vector<ToDo>& todos) = 0;
    virtual void ShowTasks(const std::vector<Task>& tasks) = 0;
    virtual void ShowToDo(const ToDo& todo) = 0;
    virtual void ShowTask(const Task& task) = 0;
    virtual int64_t InputToDo() = 0;
    virtual int64_t InputTask() = 0;
    virtual void EditToDo(const ToDo& todo) = 0;
    virtual void EditTask(const Task& task) = 0;
};

#endif //IUI_HPP
