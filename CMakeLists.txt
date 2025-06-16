cmake_minimum_required(VERSION 3.10.0)

project("2048" CXX)
option(CLOUD OFF "Enable all sanitizers")
if(CLOUD)
    add_compile_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
    add_link_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
endif(CLOUD)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/StandardProjectSettings.cmake)
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()
add_subdirectory(external/doctest)
add_subdirectory(2048)

add_executable(2048_game main.cpp)

target_sources(2048_game PRIVATE
    2048/2048.cpp
    2048/2048.h
)

target_link_libraries(2048_game PRIVATE default)

target_include_directories(2048_game PRIVATE ${CMAKE_SOURCE_DIR}/2048)
