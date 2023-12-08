#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class Pipe {
public:
  Pipe() = default;
  Pipe(const nlohmann::json &settings, const sf::Texture &texture);

  void start();

  void update();

  void draw(sf::RenderWindow &window);

  sf::FloatRect getBounds() const;

private:
  sf::Sprite sprite_;
  sf::Vector2f velocity_;
};

} // namespace ZHMGAME001