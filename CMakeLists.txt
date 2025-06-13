cmake_minimum_required(VERSION 3.10.0)

project("2048" CXX)
option(CLOUD OFF "Enable all sanitizers")
if(CLOUD)
    add_compile_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
    add_link_options(-fsanitize=undefined,address,leak,pointer-compare,pointer-subtract)
endif(CLOUD)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()
add_subdirectory(external/doctest)
add_subdirectory(2048)

# Здесь добавляем сборку основного исполняемого файла с main.cpp из корня
add_executable(2048_game main.cpp)

# Если нужны исходники из папки 2048 (например, 2048.cpp), то укажи их явно:
target_sources(2048_game PRIVATE
    2048/2048.cpp
    2048/2048.h
)

# Подключаем стандартные настройки и компиляционные опции к цели
target_link_libraries(2048_game PRIVATE default)

# Если нужно, укажи include директории, например:
target_include_directories(2048_game PRIVATE ${CMAKE_SOURCE_DIR}/2048)
