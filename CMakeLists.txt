cmake_minimum_required(VERSION 3.15)
project(mewo C)

add_executable(mewo 
    src/main.c
    src/mewo.c
    src/transforms.c
)
add_executable(frame_validation
    src/mewo.c
    src/transforms.c
    test/frame_validation.c
)
add_executable(anim_validation
    src/mewo.c
    src/transforms.c
    test/anim_validation.c
)

target_include_directories(mewo PRIVATE include/)

target_include_directories(frame_validation PRIVATE include/)
target_compile_options(frame_validation PUBLIC -g)

target_include_directories(anim_validation PRIVATE include/)
target_link_libraries(anim_validation PRIVATE ncurses)
target_compile_definitions(anim_validation PRIVATE NCURSES_WIDECHAR=1)
target_compile_options(anim_validation PUBLIC -g)
