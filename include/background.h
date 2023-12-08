#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {
class Background : public sf::Drawable {
public:
  Background() = default;
  explicit Background(const nlohmann::json &settings);

  void start();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
};
} // namespace ZHMGAME001