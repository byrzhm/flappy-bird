add_library(FLAPPY_BIRD_LIB STATIC
  bird.cpp
  pipe.cpp
  pipe_spawner.cpp
  background.cpp
  score_board.cpp
  game.cpp
)

target_link_libraries(FLAPPY_BIRD_LIB
  PRIVATE sfml-system sfml-network sfml-graphics sfml-window
  PRIVATE glm::glm
)


target_include_directories(FLAPPY_BIRD_LIB
  PRIVATE ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/nlohmann/include
)

if (MSVC) # 设置 MSVC 编译器的特定项
  target_compile_options(FLAPPY_BIRD_LIB PRIVATE "/MT")
endif()