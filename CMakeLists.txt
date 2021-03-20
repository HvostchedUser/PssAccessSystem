cmake_minimum_required(VERSION 3.0)

project(pss2)

add_executable(pss2 main.cpp)

install(TARGETS pss2 RUNTIME DESTINATION bin)
