/**
 * @file pipe_spawner.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 生成水管类实现
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "pipe_spawner.h"

static float timeSinceLastSpawn = 0.0f;

namespace ZHMGAME001 {

/// 每隔多少秒生成一个水管
const float SPAWN_RATE = 4.25f;

extern float birdWidth;
extern float screenWidth;
extern float screenHeight;

/**
 * @brief 创建水管生成器对象
 * 
 * @param settings 配置文件
 */
PipeSpawner::PipeSpawner(const nlohmann::json& settings)
  : settings_(settings)
{}

/**
 * @brief 开始生成水管
 */
void PipeSpawner::start()
{
  leftPipes_.clear();
  rightPipes_.clear();

  timeSinceLastSpawn = SPAWN_RATE;  // spawn a pipe immediately
}

/**
 * @brief 更新水管状态
 * 
 * @param deltaTime 时间间隔
 */
void PipeSpawner::update(const sf::Time& deltaTime)
{
  for (auto& pipe : leftPipes_)
  {
    pipe.update(deltaTime);
  }
  for (auto& pipe : rightPipes_)
  {
    pipe.update(deltaTime);
  }

  if (timeSinceLastSpawn > SPAWN_RATE)
  {
    rightPipes_.emplace_back(settings_);
    rightPipes_.back().start();
    timeSinceLastSpawn = 0.0f;
  }
  else
  {
    timeSinceLastSpawn = timeSinceLastSpawn + deltaTime.asSeconds();
  }

  if (!leftPipes_.empty() && leftPipes_.front().isOffScreen())
  {
    leftPipes_.pop_front();
  }

  if (!rightPipes_.empty() && rightPipes_.front().getBottomRightPosition().x < screenWidth / 2.0f - birdWidth / 2.0f)
  {
    scored_ = true;
    auto pipe = rightPipes_.front();
    rightPipes_.pop_front();
    leftPipes_.push_back(std::move(pipe));
  }
}

/**
 * @brief 绘制水管
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void PipeSpawner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (const auto& pipe : leftPipes_)
  {
    target.draw(pipe, states);
  }
  for (const auto& pipe : rightPipes_)
  {
    target.draw(pipe, states);
  }
}

/**
 * @brief 获取中间水管的上方碰撞矩形
 * 
 * @return sf::RectangleShape 碰撞矩形
 */
sf::RectangleShape PipeSpawner::getMiddleTopCollisionRect() const
{
  if (rightPipes_.empty())
  {
    return sf::RectangleShape();
  }
  return rightPipes_.front().getTopCollisionRect();
}

/**
 * @brief 获取中间水管的下方碰撞矩形
 * 
 * @return sf::RectangleShape 碰撞矩形
 */
sf::RectangleShape PipeSpawner::getMiddleBottomCollisionRect() const
{
  if (rightPipes_.empty())
  {
    return sf::RectangleShape();
  }
  return rightPipes_.front().getBottomCollisionRect();
}

/**
 * @brief 获取是否得分
 * 
 * @return true 得分
 * @return false 未得分
 */
bool PipeSpawner::getScored()
{
  bool scored = scored_;
  scored_ = false;
  return scored;
}

}  // namespace ZHMGAME001