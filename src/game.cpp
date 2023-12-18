/**
 * @file game.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 游戏类实现
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "game.h"

namespace ZHMGAME001 {

float screenWidth = 0.0f; ///< 屏幕宽度
float screenHeight = 0.0f; ///< 屏幕高度

/**
 * @brief 创建游戏对象
 * 
 * @param settings 配置文件
 */
Game::Game(const nlohmann::json& settings)
  : settings_(settings)
{
  screenWidth = settings["width"];
  screenHeight = settings["height"];

  bird_ = std::make_unique<Bird>(settings_);
  pipeSpawner_ = std::make_unique<PipeSpawner>(settings_);
  scoreBoard_ = std::make_unique<ScoreBoard>(settings_);
  background_ = std::make_unique<Background>(settings_);
}

/**
 * @brief 游戏开始
 */
void Game::start()
{
  bird_->start();
  pipeSpawner_->start();
  scoreBoard_->start();
  background_->start();
}

/**
 * @brief 更新游戏状态
 * 
 * @param deltaTime 时间间隔
 */
void Game::update(const sf::Time& deltaTime)
{
  if (gameState_ == GameState::PLAYING)
  {
    bird_->update(deltaTime);
    pipeSpawner_->update(deltaTime);
    scoreBoard_->update(pipeSpawner_->getScored());
    if (bird_->isColliding(pipeSpawner_->getMiddleTopCollisionRect()) || bird_->isColliding(pipeSpawner_->getMiddleBottomCollisionRect()))
    {
      gameState_ = GameState::GAME_OVER;
    }
  }
}

/**
 * @brief 绘制游戏对象
 * 
 * @param target 目标渲染对象
 * @param states 渲染状态
 */
void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*background_, states);
  target.draw(*bird_, states);
  target.draw(*pipeSpawner_, states);
  target.draw(*scoreBoard_, states);
}

/**
 * @brief 游戏重置
 */
void Game::reset()
{
  bird_->start();
  pipeSpawner_->start();
  scoreBoard_->start();
  gameState_ = GameState::PLAYING;
}

/**
 * @brief 获取游戏状态
 * 
 * @return GameState 游戏状态
 */
GameState Game::getGameState() const
{
  return gameState_;
}

/**
 * @brief 运行游戏
 */
void Game::run()
{
  sf::RenderWindow window(
      sf::VideoMode(static_cast<unsigned>(screenWidth),
                    static_cast<unsigned>(screenHeight)),
      "Flappy Bird",
      sf::Style::Titlebar | sf::Style::Close);

  start();

  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Event event{};

    // 处理事件
    while (window.pollEvent(event))
    {
      // 关闭窗口
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      // 鼠标左键按下
      else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
      {
        bird_->flap();
      }
      // 键盘R键按下
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
      {
        reset();
        clock.restart();
      }
    }

    sf::Time deltaTime = clock.restart();
    update(deltaTime);

    window.clear();
    window.draw(*this);
    window.display();
  }
}

}  // namespace ZHMGAME001