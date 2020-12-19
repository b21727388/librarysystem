cmake_minimum_required(VERSION 3.17)
project(LibrarySystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(LibrarySystem Main.cpp LibrarySystem.cpp LibrarySystem.h CircularLinkedList.h MovieList.h UserList.h)