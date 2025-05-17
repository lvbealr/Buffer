cmake_minimum_required(VERSION 3.10)
project(Buffer LANGUAGES CXX)

add_library(Buffer INTERFACE)

target_link_libraries(Buffer INTERFACE customWarning colorPrint)

target_include_directories(Buffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})