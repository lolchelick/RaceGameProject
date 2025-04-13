cmake_minimum_required(VERSION 3.10)
project(RaceGameProject)

set(CMAKE_CXX_STANDARD 17)


find_package(SFML 2.6.2 COMPONENTS window system graphics REQUIRED)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/include/*.h")


if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


if(MSVC)
    include_directories("C:/SFML-2.6.2/include")
endif()
if(MINGW)
    include_directories("C:/SFML-2.6.2/include")
endif()


target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    sfml-window 
    sfml-system 
    sfml-graphics
)