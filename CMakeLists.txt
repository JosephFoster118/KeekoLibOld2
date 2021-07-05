# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (KeekoLib)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib )
link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/KeekoLib/include)

add_subdirectory (KeekoLib)
add_subdirectory (tester)
add_subdirectory (SharedExample)
add_dependencies (tester KeekoLib)
add_dependencies (SharedExample KeekoLib)
add_dependencies (tester SharedExample)
