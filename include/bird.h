#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class Bird : public sf::Drawable {
public:
  Bird() = default;
  explicit Bird(const nlohmann::json &settings);

  void start();

  void update(const sf::Time &deltaTime);

  void flap();

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  bool isColliding(const sf::RectangleShape &rect) const;

private:
  sf::Vector2f getCenter() const;

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::CircleShape collisionCircle_;
  sf::Vector2f velocity_;
};

} // namespace ZHMGAME001
