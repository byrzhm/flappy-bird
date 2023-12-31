cmake_minimum_required(VERSION 3.10.0...3.26.0)
project(flappy_bird VERSION 0.1.0 LANGUAGES C CXX)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # 如果Git可用并且项目是一个Git仓库，则拉取子模块
    message(STATUS "Git found, updating submodules")

    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_SUBMOD_RESULT
    )

    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
else()
    message(WARNING "Git not found or project is not a Git repository. Submodules will not be updated.")
endif()

set(SFML_STATIC_LIBRARIES TRUE)
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

set_target_properties(flappy_bird PROPERTIES WIN32_EXECUTABLE TRUE)

if(MSVC)
    # 设置 MSVC 编译器的特定选项
    # MSVC（Microsoft Visual C++）编译器在默认情况下使用的是多线程动态链接运行时 (/MD)
    target_compile_options(flappy_bird PRIVATE "/MT")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/MinSizeRel)
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/MinSizeRel)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo)
file(COPY settings.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo)

# 生成文档
find_package(Doxygen)

# 检查是否找到 Doxygen
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile")

    # Configure the Doxyfile
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a target to generate the documentation
    add_custom_target(doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else(DOXYGEN_FOUND)
    message("Doxygen not found, cannot generate documentation")
endif(DOXYGEN_FOUND)

include(CTest)
enable_testing()

# 生成 msi 安装包
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "WIX") # 使用 WiX 作为生成器
set(CPACK_PACKAGE_EXECUTABLES "flappy_bird" "flappy_bird.exe")
install(TARGETS flappy_bird DESTINATION .)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/settings.json DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION .)
include(CPack)