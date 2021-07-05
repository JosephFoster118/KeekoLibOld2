# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (KeekoLib)
include_directories(include)
set(SOURCES
    "src/PeriodicThread.cpp"
    "src/TCPServer.cpp"
    "src/Span.cpp"
    "src/Heap.cpp"
    "src/SharedMemory.cpp"
    "src/DynamicLibrary.cpp"
    "src/ThreadPool.cpp"
)
set(HEADERS
    "include/PeriodicThread.h"
    "include/TCPServer.h"
    "include/Span.h"
    "include/Heap.h"
    "include/SharedMemory.h"
    "include/DynamicLibrary.h"
    "include/DynamicLibraryExceptions.h"
    "include/ThreadPool.h"
)

find_package(Threads REQUIRED)


add_library (KeekoLib ${SOURCES})
target_link_libraries(KeekoLib Threads::Threads dl)


install(TARGETS KeekoLib DESTINATION /usr/lib)

install(FILES ${HEADERS}
    DESTINATION /usr/include/KeekoLib
)
