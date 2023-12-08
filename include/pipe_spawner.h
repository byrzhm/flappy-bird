#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class PipeSpawner {
public:
  PipeSpawner() = default;
  PipeSpawner(const nlohmann::json &settings);

  void start();

  void update();
};

} // namespace ZHMGAME001