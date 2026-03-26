cmake_minimum_required(VERSION 3.18)
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
	message(FATAL_ERROR "Source and build directories cannot be the same.")
endif()
project(gameboy-emulator VERSION 1.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()


find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

get_target_property(SFML_LIB sfml-graphics LOCATION)
get_filename_component(SFML_LIB_DIR "${SFML_LIB}" DIRECTORY)



file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(emulator ${PROJECT_SOURCES})

target_precompile_headers(emulator PRIVATE src/common.hpp)
target_include_directories(emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(emulator PRIVATE cxx_std_20)
target_compile_options(emulator PRIVATE
    -Wall -Wextra
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Release>:-O3>
)

target_link_libraries(emulator PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(emulator PROPERTIES BUILD_RPATH "${SFML_LIB_DIR}")
