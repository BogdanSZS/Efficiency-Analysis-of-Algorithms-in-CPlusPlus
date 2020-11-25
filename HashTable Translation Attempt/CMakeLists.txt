cmake_minimum_required(VERSION 3.17)
project(C___Hash_Table)

set(CMAKE_CXX_STANDARD 14)

add_library(HashTableLibrary cmake-build-debug/HashTable.cpp cmake-build-debug/HashTable.h)
add_subdirectory(cmake-build-debug/Testing)
add_executable(C___Hash_Table main.cpp)
target_link_libraries(C___Hash_Table HashTableLibrary)
