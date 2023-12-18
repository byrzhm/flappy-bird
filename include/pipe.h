/**
 * @file pipe.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 水管类声明
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
 * @brief 水管类
 */
class Pipe : public sf::Drawable, public sf::Transformable
{
public:
  Pipe() = default;
  explicit Pipe(const nlohmann::json& settings);

  void start();

  void update(const sf::Time& deltaTime);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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

}  // namespace ZHMGAME001