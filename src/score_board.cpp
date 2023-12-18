/**
 * @file score_board.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 积分板类实现
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "score_board.h"

namespace ZHMGAME001 {

extern float screenWidth;
extern float screenHeight;

/**
 * @brief 创建积分板对象
 * 
 * @param settings 配置文件
 */
ScoreBoard::ScoreBoard(const nlohmann::json& settings)
{
  font_.loadFromFile(settings["font"]);
  scoreText_.setFont(font_);
  scoreText_.setCharacterSize(50);
  scoreText_.setFillColor(sf::Color::White);
  scoreText_.setOutlineColor(sf::Color::Black);
  scoreText_.setOutlineThickness(2.0f);
  scoreText_.setPosition(20.0f, 50.0f);
}

/**
 * @brief 积分板初始化
 */
void ScoreBoard::start()
{
  score_ = 0;
  scoreText_.setString(std::to_string(score_));
}

/**
 * @brief 更新积分板
 * 
 * @param scored 是否得分
 */
void ScoreBoard::update(bool scored)
{
  if (!scored)
  {
    return;
  }
  incrementScore();
  scoreText_.setString(std::to_string(score_));
}

/**
 * @brief 绘制积分板
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void ScoreBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(scoreText_, states);
}

/**
 * @brief 增加积分
 */
void ScoreBoard::incrementScore()
{
  score_++;
}

}  // namespace ZHMGAME001
