# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (OpenGLFun)
include_directories(include)
include_directories(include/OpenGLObjects)

set( SRCS
    "src/main.cpp"
    "src/Shape.cpp"
    "src/Rectangle.cpp"
    "src/TestClass.cpp"
    "src/OpenGLObjects/FrameBuffer.cpp"
    "src/OpenGLObjects/MultisampledFrameBuffer.cpp"
)


add_executable (OpenGLFun ${SRCS})
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(OpenGLFun -lGL -lGLU -lglfw  ${GLEW_LIBRARIES}  -lKeekoLib  -lpthread)
