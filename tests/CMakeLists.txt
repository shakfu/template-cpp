
enable_testing()

set(test_suite 
    test_main.cpp
    test_basic.cpp
    test_model.cpp
)

add_executable(test_app ${test_suite})

target_link_libraries(test_app
    model
	# Doctest
    SQLiteCpp
    sqlite3
    pthread
    dl
    m
)

add_test(NAME test_app
         COMMAND test_app)


set_target_properties(test_app PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
