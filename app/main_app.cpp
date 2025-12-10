//
// Created by nekita on 19.11.25.
//

#include <iostream>

#include "netodo/App.hpp"
#include "netodo/db_manager/TaskDBManager.hpp"
#include "netodo/db_manager/ToDoDBManager.hpp"
#include "netodo/interface/ConsolUI.hpp"

int main() {
    std::cout << "NeToDo start!\n";
    std::cout << "Name of NeToDo base: ";
    std::string base_name;
    std::cin >> base_name;
    base_name += ".db";
    TaskDBManager task_db(base_name);
    ToDoDBManager todo_db(base_name);
    App app(todo_db, task_db);
    ConsolUI ui(std::cin, std::cout, app);
    ui.Show();
}