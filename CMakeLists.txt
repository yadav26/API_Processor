# ***********************************************************************************************
#         Anshul Yadav
#         er.anshulyadav@gmail.com
#         yadav26@github
#         This is for tritium api processor
# ************************************************************************************************

cmake_minimum_required(VERSION 3.0)
project(tritium_project)
file(GLOB_RECURSE sources      sources/*.cpp sources/*.hpp)

add_subdirectory(sources/CommandEditor)
add_subdirectory(sources/CommandHandlers)
include_directories(sources/CommandEditor sources/CommandHandlers)
add_executable(api_parser ${sources} )
set_property(TARGET api_parser PROPERTY CXX_STANDARD 17)
set_property(TARGET api_parser PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_options(api_parser PUBLIC -std=c++1y -Wall )
