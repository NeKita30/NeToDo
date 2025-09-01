add_executable(note_test note_test.cpp)
target_link_libraries(note_test gtest gtest_main netodo_notes)
target_include_directories(note_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})