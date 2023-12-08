add_library(FLAPPY_BIRD_LIB STATIC
  flappy_bird.cpp
)

target_link_libraries(FLAPPY_BIRD_LIB
  PRIVATE sfml-system sfml-network sfml-graphics sfml-window
)


target_include_directories(FLAPPY_BIRD_LIB
  PRIVATE ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/nlohmann/include
)