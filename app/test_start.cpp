//
// Created by nekita on 29.08.25.
//

#include "netodo/App.hpp"
#include "netodo/interface/ConsolUI.hpp"
#include "netodo/db_manager/TaskDBManager.hpp"
#include "netodo/db_manager/ToDoDBManager.hpp"
#include "netodo/notes/Note.hpp"
#include "iostream"

int main() {
    TaskDBManager task_db("test_start.db");
    ToDoDBManager todo_db("test_start.db");
    App app(todo_db, task_db);
    ConsolUI ui(std::cin, std::cout, app);
    ui.Show();
}
