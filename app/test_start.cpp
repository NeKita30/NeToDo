//
// Created by nekita on 29.08.25.
//

#include <fstream>
#include <iostream>

#include "netodo/App.hpp"
#include "netodo/db_manager/TaskDBManager.hpp"
#include "netodo/db_manager/ToDoDBManager.hpp"
#include "netodo/interface/ConsolUI.hpp"
#include "netodo/notes/Note.hpp"

int main() {
    std::ifstream fs("input_test_start.txt");
    TaskDBManager task_db("test_start.db");
    ToDoDBManager todo_db("test_start.db");
    App app(todo_db, task_db);
    ConsolUI ui(fs, std::cout, app);
    ui.Show();
}
