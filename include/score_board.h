/**
 * @file score_board.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 积分板类声明
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
 * @brief 积分板类
 */
class ScoreBoard : public sf::Drawable
{
public:
  ScoreBoard() = default;
  explicit ScoreBoard(const nlohmann::json& settings);

  void start();

  void update(bool scored);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  void incrementScore();

private:
  sf::Font font_;
  sf::Text scoreText_;
  int score_{0};
};

}  // namespace ZHMGAME001