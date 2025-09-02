add_library(netodo_notes SHARED src/notes/Note.cpp
                                src/notes/ToDo.cpp
                                src/notes/Task.cpp)

target_include_directories(netodo_notes PUBLIC include)