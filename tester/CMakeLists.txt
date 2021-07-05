# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (tester)
include_directories(include)
include_directories()
set(SOURCES src/main.cpp)
find_package(Threads REQUIRED)



add_executable (tester ${SOURCES})
target_link_libraries(tester KeekoLib Threads::Threads dl)
