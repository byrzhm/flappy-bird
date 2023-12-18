/**
 * @file pipe.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 水管类实现
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <random>

#include "pipe.h"

namespace ZHMGAME001 {

const float MAX_HOLE_SIZE = 300.0f; ///< 水管最大空隙大小
const float MIN_HOLE_SIZE = 200.0f; ///< 水管最小空隙大小
const float PIPE_SPEED = 100.0f; ///< 水管移动速度

extern float screenWidth;
extern float screenHeight;

/**
 * @brief 创建水管对象
 * 
 * @param settings 配置文件
 */
Pipe::Pipe(const nlohmann::json& settings)
{
  if (!texture_.loadFromFile(settings["pipe_img_path"]))
  {
    throw std::runtime_error("Failed to load pipe image");
  }

  topSprite_.setTexture(texture_);
  float scaleX = 0.125f * screenWidth / topSprite_.getGlobalBounds().getSize().x;
  float scaleY = screenHeight / topSprite_.getGlobalBounds().getSize().y;

  topSprite_.setScale(scaleX, scaleY);

  bottomSprite_.setTexture(texture_);
  bottomSprite_.setScale(scaleX, scaleY);
  bottomSprite_.setRotation(180.0f);

  sf::Vector2f pipeSize = topSprite_.getGlobalBounds().getSize();
  topCollisionRect_.setSize(pipeSize);
  topCollisionRect_.setFillColor(sf::Color::Transparent);
  // topCollisionRect_.setOutlineColor(sf::Color::Red);
  // topCollisionRect_.setOutlineThickness(1.0f);

  bottomCollisionRect_.setSize(pipeSize);
  bottomCollisionRect_.setOrigin(pipeSize.x, pipeSize.y);
  bottomCollisionRect_.setFillColor(sf::Color::Transparent);
  // bottomCollisionRect_.setOutlineColor(sf::Color::Red);
  // bottomCollisionRect_.setOutlineThickness(1.0f);
}

/**
 * @brief 开始生成水管
 */
void Pipe::start()
{
  std::mt19937 rng(std::random_device{}());

  std::uniform_real_distribution<float> holeSizeDist(MIN_HOLE_SIZE, MAX_HOLE_SIZE);
  float holeSize = holeSizeDist(rng);

  std::uniform_real_distribution<float> holePosDist(holeSize / 2.0f, screenHeight - holeSize / 2.0f);
  float holePos = holePosDist(rng);

  topSprite_.setPosition(screenWidth, holePos - holeSize / 2.0f - topSprite_.getGlobalBounds().height);
  bottomSprite_.setPosition(screenWidth + bottomSprite_.getGlobalBounds().width, holePos + holeSize / 2.0f + bottomSprite_.getGlobalBounds().height);

  topCollisionRect_.setPosition(topSprite_.getPosition());
  bottomCollisionRect_.setPosition(bottomSprite_.getPosition());
}

/**
 * @brief 更新水管状态
 * 
 * @param deltaTime 时间间隔
 */
void Pipe::update(const sf::Time& deltaTime)
{
  sf::Vector2f position = topSprite_.getPosition();
  position.x -= PIPE_SPEED * deltaTime.asSeconds();
  topSprite_.setPosition(position);
  topCollisionRect_.setPosition(position);

  position = bottomSprite_.getPosition();
  position.x -= PIPE_SPEED * deltaTime.asSeconds();
  bottomSprite_.setPosition(position);
  bottomCollisionRect_.setPosition(position);
}

/**
 * @brief 绘制水管
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(topSprite_, states);
  target.draw(bottomSprite_, states);
  target.draw(topCollisionRect_, states);
  target.draw(bottomCollisionRect_, states);
}

/**
 * @brief 水管是否已经离开屏幕
 * 
 * @return true 离开屏幕
 * @return false 没有离开屏幕
 */
bool Pipe::isOffScreen() const
{
  return topSprite_.getPosition().x < -topSprite_.getGlobalBounds().width;
}

/**
 * @brief 获取水管的右上角位置
 * 
 * @return sf::Vector2f 水管的右上角位置
 */
sf::Vector2f Pipe::getBottomRightPosition() const
{
  return bottomSprite_.getPosition();
}

/**
 * @brief 获取上方水管的碰撞矩形
 * 
 * @return sf::RectangleShape 上方水管的碰撞矩形
 */
sf::RectangleShape Pipe::getTopCollisionRect() const
{
  return topCollisionRect_;
}

/**
 * @brief 获取下方水管的碰撞矩形
 * 
 * @return sf::RectangleShape 下方水管的碰撞矩形
 */
sf::RectangleShape Pipe::getBottomCollisionRect() const
{
  sf::RectangleShape rect;
  rect.setSize(bottomCollisionRect_.getSize());
  rect.setPosition(bottomCollisionRect_.getPosition() - bottomCollisionRect_.getSize());
  return rect;
}

}  // namespace ZHMGAME001
