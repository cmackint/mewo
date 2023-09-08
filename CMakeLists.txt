cmake_minimum_required(VERSION 3.15)
project(mewo C)

add_executable(mewo 
    src/mewo.c
    src/main.c
)

target_include_directories(mewo PRIVATE include/)
