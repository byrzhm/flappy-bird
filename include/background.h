/**
 * @file background.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 背景类声明
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
 * @brief 背景类
 */
class Background : public sf::Drawable
{
public:
  Background() = default;
  explicit Background(const nlohmann::json& settings);

  void start();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  sf::Texture texture_;
  sf::Sprite sprite_;
};

}  // namespace ZHMGAME001