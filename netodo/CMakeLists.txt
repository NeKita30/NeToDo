add_library(netodo_notes SHARED src/notes/Note.cpp
        include/netodo/notes/Note.hpp)

target_include_directories(netodo_notes PUBLIC include)