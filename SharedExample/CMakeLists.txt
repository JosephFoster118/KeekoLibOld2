# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (SharedExample)
include_directories(include)
set(SOURCES
    src/Loader.cpp
)
set(HEADERS
    include/Loader.cpp
)
find_package(Threads REQUIRED)

add_library (SharedExample SHARED ${SOURCES})
target_link_libraries(SharedExample KeekoLib Threads::Threads dl)
