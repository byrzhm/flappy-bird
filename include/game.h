/**
 * @file game.h
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 游戏类声明
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <memory>

#include "background.h"
#include "bird.h"
#include "pipe_spawner.h"
#include "score_board.h"


namespace ZHMGAME001 {

/**
 * @brief 游戏状态
 */
enum class GameState
{
  PLAYING,
  GAME_OVER
};

/**
 * @brief 游戏类
 */
class Game : public sf::Drawable
{
public:
  Game() = delete;
  explicit Game(const nlohmann::json& settings);

  void run();

private:
  void start();

  void update(const sf::Time& deltaTime);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void reset();

  GameState getGameState() const;

private:
  std::unique_ptr<Bird> bird_;
  std::unique_ptr<PipeSpawner> pipeSpawner_;
  std::unique_ptr<ScoreBoard> scoreBoard_;
  std::unique_ptr<Background> background_;
  const nlohmann::json& settings_;
  GameState gameState_{GameState::PLAYING};
};
}  // namespace ZHMGAME001