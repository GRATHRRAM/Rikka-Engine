cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(Rikka_Engine VERSION 1.0)

set(Rikka_Core_Src
    ./src/rikka_core/core.c
    ./src/rikka_core/shaders.c
    ./src/rikka_core/renderer.c
    ./src/rikka_core/renderer_shaders.c
)

#Copy Staff to build

add_custom_target(copy_header ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/src/rikka_core.h
    ${PROJECT_SOURCE_DIR}/demos
    COMMENT "Copying Rikka_Core.h"
)

add_custom_target(copy_header2 ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/src/rikka_datatypes.h
    ${PROJECT_SOURCE_DIR}/demos
    COMMENT "Copying Rikka_Core.h"
)

if(static STREQUAL "true")
    add_compile_options(-static)
endif()

if(debug STREQUAL "true")
    add_compile_options(-g)
else()
    add_compile_options(-O2)
endif()


#if(build_windows STREQUAL "true" AND NOT WIN32)
#     set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-gcc)
#     include_directories(./include)
#     link_directories(./lib)
#     add_compile_options(-L./lib -I./include)
#else()
#     set(CMAKE_CXX_COMPILER gcc)
#endif()

add_compile_options(-Wall -Wextra)
link_directories(${CMAKE_BINARY_DIR})

if(shared STREQUAL "true")
    add_library(rikkacore SHARED ${Rikka_Core_Src})
else() 
    add_library(rikkacore STATIC ${Rikka_Core_Src})
endif()

add_executable(BasicWindow ${PROJECT_SOURCE_DIR}/demos/BasicWindow.c)
add_executable(Rect        ${PROJECT_SOURCE_DIR}/demos/Rect.c)

target_link_libraries(BasicWindow PRIVATE rikkacore m glfw GL GLEW)
target_link_libraries(Rect        PRIVATE rikkacore m glfw GL GLEW)
