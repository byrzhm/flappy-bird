/**
 * @file bird.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 鸟类实现
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "bird.h"

static float maxHeight = 0.0f;

namespace ZHMGAME001 {

const float GRAVITY = 100.0f; ///< 重力加速度
const float JUMP_VELOCITY = 80.0f; ///< 跳跃速度

float birdWidth = 0.0f; ///< 鸟的宽度
float birdHeight = 0.0f; ///< 鸟的高度

extern float screenWidth;
extern float screenHeight;

/**
 * @brief 创建鸟对象
 * 
 * @param settings 配置文件
 */
Bird::Bird(const nlohmann::json& settings)
{
  if (!texture_.loadFromFile(settings["bird_img_path"]))
  {
    throw std::runtime_error("Failed to load bird image");
  }

  sprite_.setTexture(texture_);
  sprite_.setScale(0.2f, 0.2f);
  sf::Vector2f birdSize = sprite_.getGlobalBounds().getSize();
  birdWidth = birdSize.x;
  birdHeight = birdSize.y;

  maxHeight = screenHeight - birdSize.y;

  collisionCircle_.setRadius(birdSize.x / 2);
  collisionCircle_.setOrigin(collisionCircle_.getRadius(), collisionCircle_.getRadius());
  collisionCircle_.setFillColor(sf::Color::Transparent);
  // 碰撞检测用
  // collisionCircle_.setOutlineColor(sf::Color::Red);
  // collisionCircle_.setOutlineThickness(1.0f);
}

/**
 * @brief 设置鸟的位置以及速度
 */
void Bird::start()
{
  sprite_.setPosition((screenWidth - birdWidth) / 2,
                      (screenHeight - birdHeight) / 2);
  collisionCircle_.setPosition(getCenter());

  velocity_ = sf::Vector2f(0.0f, 0.0f);
}

/**
 * @brief 更新鸟的位置
 * 
 * @param deltaTime 时间间隔
 */
void Bird::update(const sf::Time& deltaTime)
{
  velocity_.y += GRAVITY * deltaTime.asSeconds();
  float positionY = sprite_.getPosition().y + velocity_.y * deltaTime.asSeconds();
  if (positionY > maxHeight)
  {
    positionY = maxHeight;
    velocity_.y = 0.0f;
  }
  else if (positionY < 0.0f)
  {
    positionY = 0.0f;
    velocity_.y = 0.0f;
  }
  sprite_.setPosition(sprite_.getPosition().x, positionY);
  collisionCircle_.setPosition(getCenter());
}

/**
 * @brief 跳跃
 */
void Bird::flap()
{
  if (velocity_.y < 0.0f && velocity_.y < -2.0f * JUMP_VELOCITY)
  {
    velocity_.y += velocity_.y / 2.0f;
  }
  else
  {
    velocity_.y = -JUMP_VELOCITY;
  }
}

/**
 * @brief 绘制鸟
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(sprite_, states);
  target.draw(collisionCircle_, states);
}

/**
 * @brief 获取鸟的中心位置
 * 
 * @return sf::Vector2f 鸟的中心位置
 */
sf::Vector2f Bird::getCenter() const
{
  sf::Vector2f birdSize = sprite_.getGlobalBounds().getSize();
  return sprite_.getPosition() + sf::Vector2f{birdSize.x / 2 - 1.0f, birdSize.y / 2 + 9.0f};
}

/**
 * @brief 判断鸟是否与矩形碰撞
 * 
 * @param rect 矩形
 * @return true 碰撞
 * @return false 没有碰撞
 */
bool Bird::isColliding(const sf::RectangleShape& rect) const
{
  if (rect.getSize() == sf::Vector2f(0.0f, 0.0f))
  {
    return false;
  }

  sf::Vector2f rectSize = rect.getSize();
  sf::Vector2f rectPosition = rect.getPosition();
  sf::Vector2f birdCenter = getCenter();
  float birdRadius = collisionCircle_.getRadius();

  glm::vec2 center(birdCenter.x, birdCenter.y);
  glm::vec2 rect_half_extents(rectSize.x / 2, rectSize.y / 2);
  glm::vec2 rect_center(
      rectPosition.x + rect_half_extents.x,
      rectPosition.y + rect_half_extents.y);

  glm::vec2 difference = center - rect_center;
  glm::vec2 clamped = glm::clamp(difference, -rect_half_extents, rect_half_extents);
  glm::vec2 closest = rect_center + clamped;
  difference = closest - center;

  return glm::length(difference) < birdRadius;
}

}  // namespace ZHMGAME001