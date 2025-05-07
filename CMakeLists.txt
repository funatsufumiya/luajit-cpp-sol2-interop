cmake_minimum_required(VERSION 3.10)
project(luajit-cpp-sol2-interop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED luajit)

set(SOURCES
    src/example.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${LUAJIT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/external/sol2/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LUAJIT_LIBRARIES}
)

file(COPY scripts DESTINATION ${CMAKE_BINARY_DIR})
