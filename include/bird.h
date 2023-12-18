/**
 * @file bird.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 鸟类声明
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

/**
 * @brief 鸟类
 */
class Bird : public sf::Drawable
{
public:
  Bird() = default;
  explicit Bird(const nlohmann::json& settings);

  void start();

  void update(const sf::Time& deltaTime);

  void flap();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  bool isColliding(const sf::RectangleShape& rect) const;

private:
  sf::Vector2f getCenter() const;

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  sf::CircleShape collisionCircle_;
  sf::Vector2f velocity_;
};

}  // namespace ZHMGAME001
