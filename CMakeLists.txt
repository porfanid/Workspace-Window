cmake_minimum_required(VERSION 3.28)
project(workspace-window)

set(CMAKE_CXX_STANDARD 17)
find_package(X11 REQUIRED)

add_executable(workspace-window src/main.cpp)

install(TARGETS workspace-window RUNTIME DESTINATION bin)

target_link_libraries(workspace-window X11)
