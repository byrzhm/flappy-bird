/**
 * @file background.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 背景类实现
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "background.h"

namespace ZHMGAME001 {
extern float screenWidth;
extern float screenHeight;

/**
 * @brief 创建背景对象
 * 
 * @param settings 配置文件
 */
Background::Background(const nlohmann::json& settings)
{
  if (!texture_.loadFromFile(settings["background_img_path"]))
  {
    throw std::runtime_error("Failed to load background image");
  }
  sprite_.setTexture(texture_);

  float scaleX = screenWidth / sprite_.getGlobalBounds().getSize().x;
  float scaleY = screenHeight / sprite_.getGlobalBounds().getSize().y;
  sprite_.setScale(scaleX, scaleY);
}

/**
 * @brief 背景初始化
 */
void Background::start() {}

/**
 * @brief 绘制背景
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(sprite_, states);
}

}  // namespace ZHMGAME001