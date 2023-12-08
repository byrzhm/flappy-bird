#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class Bird {
public:
  Bird() = default;
  Bird(const nlohmann::json &settings, const sf::Texture &texture);

  void start();

  void update();

private:
  sf::Sprite sprite_;
  sf::CircleShape collisionCircle_;
};

} // namespace ZHMGAME001
