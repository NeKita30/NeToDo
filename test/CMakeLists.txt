add_executable(note_test note_test.cpp)
target_link_libraries(note_test gtest gtest_main netodo_notes)
target_include_directories(note_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(db_test db_test.cpp)
target_link_libraries(db_test gtest gtest_main db_manager)
target_include_directories(db_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})