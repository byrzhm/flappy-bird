#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class Pipe : public sf::Drawable, public sf::Transformable {
public:
  Pipe() = default;
  explicit Pipe(const nlohmann::json &settings);

  void start();

  void update(const sf::Time &deltaTime);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  bool isOffScreen() const;

  sf::Vector2f getBottomRightPosition() const;

  sf::RectangleShape getTopCollisionRect() const;

  sf::RectangleShape getBottomCollisionRect() const;

private:
  sf::Texture texture_;
  sf::Sprite topSprite_;
  sf::Sprite bottomSprite_;
  sf::RectangleShape topCollisionRect_;
  sf::RectangleShape bottomCollisionRect_;
};

} // namespace ZHMGAME001