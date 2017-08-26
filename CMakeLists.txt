cmake_minimum_required(VERSION 3.7)
set(projectName Pong)
project(${projectName})

set(CMAKE_CXX_STANDARD 11)

file(GLOB DEPS_SOURCES ext/glad/src/glad.c)
include_directories("ext/glm/" "ext/glfw/include" "ext/glad/include" "ext/imgui")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(ext/glfw)

file(GLOB IMGUI_SOURCE ext/imgui/*.cpp ext/imgui/*.h)
set(SOURCE_FILES main.cpp src/GLwin.hpp src/Shaders.hpp src/PingPong.hpp src/Slider.hpp src/Ball.hpp src/Walls.hpp src/Line.hpp)

add_executable(${projectName} ${SOURCE_FILES}  ${DEPS_SOURCES} ${IMGUI_SOURCE})
target_link_libraries(${projectName} glfw ${GLFW_LIBRARIES} ${PLATFORM_LINK} )