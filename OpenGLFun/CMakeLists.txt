# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (OpenGLFun)
include_directories(include)

set(SRCS "main.cpp" "src/Shape.cpp" "src/Rectangle.cpp" "src/TestClass.cpp"
    "src/FrameBuffer.cpp" "src/MultisampledFrameBuffer.cpp")


add_executable (OpenGLFun ${SRCS})
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(OpenGLFun -lGL -lGLU -lglut ${GLEW_LIBRARIES} -lpthread -lKeekoLib)
