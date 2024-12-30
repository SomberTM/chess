cmake_minimum_required(VERSION 3.10)

project(ChessProject)

set(CMAKE_C_STANDARD 11)

include_directories(src)

file(GLOB SRC_FILES src/*.c)

add_executable(chess ${SRC_FILES})

option(BUILD_TESTS "Build the test executables" ON)

if (BUILD_TESTS)
    list(FILTER SRC_FILES EXCLUDE REGEX "src/main.c")
    file(GLOB TEST_FILES test/*_test.c)

    foreach(TEST_FILE ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_FILE} ${SRC_FILES})
        set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
    endforeach()
endif()
