#include "game.h"

namespace ZHMGAME001 {

float screenWidth = 0.0f;
float screenHeight = 0.0f;

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

void Game::start()
{
  bird_->start();
  pipeSpawner_->start();
  scoreBoard_->start();
  background_->start();
}

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

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*background_, states);
  target.draw(*bird_, states);
  target.draw(*pipeSpawner_, states);
  target.draw(*scoreBoard_, states);
}

void Game::reset()
{
  bird_->start();
  pipeSpawner_->start();
  scoreBoard_->start();
  gameState_ = GameState::PLAYING;
}

GameState Game::getGameState() const
{
  return gameState_;
}

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

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
      {
        bird_->flap();
      }
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