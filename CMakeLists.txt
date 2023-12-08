cmake_minimum_required(VERSION 3.26.0)
project(flappy_bird VERSION 0.1.0 LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")


find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
message(STATUS "SFML_DIR: ${SFML_DIR}")
message(STATUS "SFML_VERSION: ${SFML_VERSION}")

find_package(glm CONFIG REQUIRED)

add_subdirectory(3rdparty)
add_subdirectory(src)

add_executable(flappy_bird main.cpp)

target_link_libraries(flappy_bird 
    PRIVATE sfml-system sfml-network sfml-graphics sfml-window
    PRIVATE FLAPPY_BIRD_LIB
)

target_include_directories(flappy_bird
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/nlohmann/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

