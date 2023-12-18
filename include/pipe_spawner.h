/**
 * @file pipe_spawner.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 生成水管类声明
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <nlohmann/json.hpp>


#include "pipe.h"

namespace ZHMGAME001 {

/**
 * @brief 生成水管类
 */
class PipeSpawner : public sf::Drawable
{
public:
  PipeSpawner() = delete;
  explicit PipeSpawner(const nlohmann::json& settings);

  void start();

  void update(const sf::Time& deltaTime);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  sf::RectangleShape getMiddleTopCollisionRect() const;

  sf::RectangleShape getMiddleBottomCollisionRect() const;

  bool getScored();

private:
  std::deque<Pipe> leftPipes_;
  std::deque<Pipe> rightPipes_;
  const nlohmann::json& settings_;
  bool scored_{false};
};

}  // namespace ZHMGAME001