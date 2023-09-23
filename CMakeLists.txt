cmake_minimum_required(VERSION 3.20)

project("some-application"
    VERSION 0.9.1
    DESCRIPTION "A project with nested library"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SomeLibrary)
