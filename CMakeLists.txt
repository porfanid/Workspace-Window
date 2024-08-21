cmake_minimum_required(VERSION 3.28)
project(workspace_window)

set(CMAKE_CXX_STANDARD 17)
find_package(X11 REQUIRED)

add_executable(workspace_window src/main.cpp)

target_link_libraries(workspace_window X11)
