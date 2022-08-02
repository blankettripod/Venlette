cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
project(Venlette CXX)

add_library(venlette STATIC Venlette/src/Util/Logging.cpp Venlette/include/Util/Logging.h Venlette/include/Core/common.h Venlette/include/Core/internal.h Venlette/include/venlette Venlette/src/Core/Engine.cpp Venlette/include/Core/Engine.h Venlette/src/Application/Application.cpp Venlette/include/Application/Application.h Venlette/include/Core/Events/Event.h Venlette/src/Core/Events/EventManager.cpp Venlette/include/Core/Events/EventManager.h Venlette/src/Core/Events/IEventListener.cpp Venlette/include/Core/Events/IEventListener.h Venlette/src/Core/Thread/ThreadManager.cpp Venlette/include/Core/Thread/ThreadManager.h)
add_executable(venlette_test Testing/src/main.cpp)

add_subdirectory(Third_Party/spdlog)

add_compile_definitions(SPDLOG_COMPILED_LIB GLFW_INCLUDE_NONE GLFW_BUILD_STATIC)

target_include_directories(venlette_test PUBLIC Venlette/include test/include)
target_include_directories(venlette PUBLIC Venlette/include)

target_link_libraries(venlette_test venlette)
target_link_libraries(venlette spdlog)

target_compile_options(venlette_test PRIVATE -fsized-deallocation)
target_compile_options(venlette PRIVATE -fsized-deallocation)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)