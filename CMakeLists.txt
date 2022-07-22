cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(Venlette_engine)


add_library(venlette Venlette/include/Core/common.h Venlette/include/venlette Venlette/src/Application/Application.cpp Venlette/include/Application/Application.h)
add_executable(venlette_test test/src/main.cpp)

add_subdirectory(Venlette/Vendor/spdlog)

add_compile_definitions(SPDLOG_COMPILED_LIB)

target_include_directories(venlette_test PUBLIC Venlette/include test/include)
target_include_directories(venlette PUBLIC Venlette/include)

target_link_libraries(venlette_test venlette)
target_link_libraries(venlette spdlog)