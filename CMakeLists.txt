cmake_minimum_required(VERSION 3.1)

set(PROJECT screw_geometry)
project(${PROJECT})
set(EXEC ${PROJECT})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ggdb")

file(GLOB_RECURSE SOURCES "src/*.cpp")
message(${SOURCES})

add_executable(${EXEC} ${SOURCES})

target_include_directories(${PROJECT} PRIVATE src/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT} OpenGL::GL)

add_subdirectory(lib/glad)
target_link_libraries(${PROJECT} glad)

set(glm_DIR lib/glm/cmake/glm)
find_package(glm REQUIRED)
target_link_libraries(${PROJECT} glm::glm)

target_include_directories(${PROJECT} PRIVATE lib/stb_image)

target_include_directories(${PROJECT} PRIVATE lib/OBJ-Loader/Source)

add_definitions(-DGLFW_INCLUDE_NONE)
