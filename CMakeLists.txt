cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(Venlette_engine)


add_library(venlette Venlette/include/Core/common.h Venlette/include/venlette Venlette/src/Core/Application/Application.cpp Venlette/include/Core/Application/Application.h Venlette/src/Util/Logging/Logger.cpp Venlette/include/Util/Logging/Logger.h Venlette/src/Core/System.cpp Venlette/include/Core/System.h Venlette/include/Core/Events/Event.h Venlette/src/Core/Events/EventManager.cpp Venlette/include/Core/Events/EventManager.h Venlette/src/Core/Events/IEventListener.cpp Venlette/include/Core/Events/IEventListener.h Venlette/src/Window/WindowManager.cpp Venlette/include/Window/WindowManager.h Venlette/src/Window/Window.cpp Venlette/include/Window/Window.h)
add_executable(venlette_test test/src/main.cpp)

add_subdirectory(Venlette/Vendor/spdlog)
add_subdirectory(Venlette/Vendor/glfw)

add_compile_definitions(SPDLOG_COMPILED_LIB GLFW_INCLUDE_NONE GLFW_BUILD_STATIC)

target_include_directories(venlette_test PUBLIC Venlette/include test/include)
target_include_directories(venlette PUBLIC Venlette/include)

target_link_libraries(venlette_test venlette)
target_link_libraries(venlette spdlog glfw)

target_compile_options(venlette_test PRIVATE -fsized-deallocation)
target_compile_options(venlette PRIVATE -fsized-deallocation)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)