#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {
class Backgound : public sf::Drawable {
public:
  Backgound() = default;
  explicit Backgound(const nlohmann::json &settings);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
};
} // namespace ZHMGAME001