cmake_minimum_required(VERSION 3.15)
project(mewo C)

add_executable(mewo 
    src/mewo.c
    src/main.c
)
add_executable(frame_validation
    src/mewo.c
    test/frame_validation.c
)

target_include_directories(mewo PRIVATE include/)

target_include_directories(frame_validation PRIVATE include/)
target_link_libraries(frame_validation PRIVATE ncurses)
target_compile_definitions(frame_validation PRIVATE NCURSES_WIDECHAR=1)
target_compile_options(frame_validation PUBLIC -g)
