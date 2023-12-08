cmake_minimum_required(VERSION 3.26.0)
project(flappy_bird VERSION 0.1.0 LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

add_subdirectory(3rdparty)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
message(STATUS "SFML_DIR: ${SFML_DIR}")
message(STATUS "SFML_VERSION: ${SFML_VERSION}")

include(CTest)
enable_testing()

add_executable(flappy_bird main.cpp)

target_link_libraries(flappy_bird PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/nlohmann/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

