cmake_minimum_required(VERSION 3.20)
project(Starstruck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# --- SFML (dinâmico) ---
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

message(STATUS "SFML Include: ${SFML_INCLUDE_DIR}")

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

# --- Executável ---
add_executable(Starstruck
    src/main.cpp
    src/Engine/application.cpp
    src/Engine/statemachine.cpp
    src/Entities/bullet.cpp
    src/Entities/map.cpp
    src/Entities/player.cpp
    src/Entities/score.cpp
    src/States/gamestate.cpp
    src/States/menustate.cpp
)

# --- Includes ---
target_include_directories(Starstruck PRIVATE
    ${SFML_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/Engine
    ${CMAKE_SOURCE_DIR}/src/Entities
    ${CMAKE_SOURCE_DIR}/src/States
)

# --- Link com bibliotecas SFML ---
target_link_libraries(Starstruck
    ${SFML_LIBRARY_DIR}/libsfml-graphics.a
    ${SFML_LIBRARY_DIR}/libsfml-window.a
    ${SFML_LIBRARY_DIR}/libsfml-system.a
    ${SFML_LIBRARY_DIR}/libsfml-audio.a
    -lws2_32
    -lopengl32
    -lwinmm
    -lgdi32
)

# --- Copiar DLLs automaticamente ---
file(GLOB SFML_DLLS "${SFML_ROOT}/bin/*.dll")
if(SFML_DLLS)
    add_custom_command(TARGET Starstruck POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_DLLS} $<TARGET_FILE_DIR:Starstruck>
    )
endif()

message(STATUS "Configuration complete!")