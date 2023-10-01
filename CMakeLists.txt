cmake_minimum_required(VERSION 3.21)

project("ip_filter" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_subdirectory(libs)

add_executable(${PROJECT_NAME})
add_executable(tests
    tests/ipfilter.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
)

target_include_directories(tests 
    PRIVATE 
        ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        IpFilter)
target_link_libraries(tests 
    PRIVATE 
        ${GTEST_BOTH_LIBRARIES} IpFilter)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic)
    target_compile_options(tests PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
