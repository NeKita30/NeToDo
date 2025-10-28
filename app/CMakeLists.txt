add_executable(test_start test_start.cpp)
target_link_libraries(test_start netodo_notes netodo_app interface db_manager)
FILE(COPY_FILE input_test_start.txt ${CMAKE_CURRENT_BINARY_DIR}/input_test_start.txt)