project(Builder)

cmake_minimum_required(VERSION 2.8)

#flag for c++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set(MY_SEARCHING_HPP_FOLDER "")
set(MY_SEARCHING_CPP_FOLDER "")

list(APPEND MY_SEARCHING_HPP_FOLDER "src/*.hpp")
list(APPEND MY_SEARCHING_CPP_FOLDER "src/*.cpp")

message("CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    add_definitions(-DSDL_MAIN_HANDLED) #undefined reference main() winmain()
    list(APPEND MY_SEARCHING_HPP_FOLDER "windows/include/SDL2/*.hpp" "windows/include/SDL2/*.h")
    find_library(SDL2_LIBRARY NAME SDL2 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/windows/lib/SDL2/ NO_DEFAULT_PATH)
    set(MY_SEARCHING_DLL_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/windows/dll/SDL2/*.dll")
    file(GLOB_RECURSE DLL_FILES ${MY_SEARCHING_DLL_FOLDER})
    message("windows detected")
else ()
    list(APPEND MY_SEARCHING_HPP_FOLDER "ubuntu/include/SDL2/*.hpp" "ubuntu/include/SDL2/*.h")
    find_library(SDL2_LIBRARY NAME libSDL2-2.0.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ubuntu/lib/SDL2/ NO_DEFAULT_PATH)
    message("ubuntu detected")
endif (WIN32)

message("SDL2_LIBRARY = " ${SDL2_LIBRARY})

file(GLOB_RECURSE EXECUTABLE_FILES ${MY_SEARCHING_CPP_FOLDER})
file(GLOB_RECURSE HEADER_FILES ${MY_SEARCHING_HPP_FOLDER})

#message("EXECUTABLE_FILES = " ${EXECUTABLE_FILES})
#message("HEADER_FILES = " ${HEADER_FILES})

set (ALL_INCLUDE_DIRS "")
foreach (_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND ALL_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES ALL_INCLUDE_DIRS)

#adding executables
add_executable(builder ${EXECUTABLE_FILES} ${HEADER_FILES})

include_directories(${ALL_INCLUDE_DIRS})
target_link_libraries (builder ${SDL2_LIBRARY})

message("MY_SEARCHING_DLL_FOLDER = " ${MY_SEARCHING_DLL_FOLDER})
message("DLL_FILES = " ${DLL_FILES})
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY = " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if (WIN32)
    ADD_CUSTOM_COMMAND (TARGET builder POST_BUILD COMMAND ${CMAKE_COMMAND} 
    -E copy_if_different
    ${DLL_FILES}              
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif (WIN32)
