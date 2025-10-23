add_library(netodo_notes SHARED src/notes/Note.cpp
                                src/notes/ToDo.cpp
                                src/notes/Task.cpp)

target_include_directories(netodo_notes PUBLIC include)

find_package(SQLiteCpp REQUIRED)
add_library(db_manager SHARED src/db_manager/DBManager.cpp
                              src/db_manager/ToDoDBManager.cpp
                              src/db_manager/TaskDBManager.cpp)
target_include_directories(db_manager PUBLIC include)
#target_link_libraries(db_manager PRIVATE SQLiteCpp sqlite3)
target_link_libraries(db_manager PUBLIC netodo_notes SQLiteCpp sqlite3)