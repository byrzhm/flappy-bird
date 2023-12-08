#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

#include "bird.h"
#include "pipe_spawner.h"
#include "background.h"
#include "score_board.h"

enum class GameState
{
  Playing,
  GameOver
};

int main()
{
  nlohmann::json settings;
  std::ifstream settingsFile("settings.json");

  if (!settingsFile.is_open())
  {
    return EXIT_FAILURE;
  }

  settingsFile >> settings;

  float screenWidth = settings["width"];
  float screenHeight = settings["height"];

  sf::RenderWindow window(
      sf::VideoMode(static_cast<unsigned>(screenWidth),
                    static_cast<unsigned>(screenHeight)),
      "Flappy Bird",
      sf::Style::Titlebar | sf::Style::Close);

  ZHMGAME001::Backgound background(settings);
  ZHMGAME001::Bird bird(settings);
  ZHMGAME001::PipeSpawner pipeSpawner(settings);
  ZHMGAME001::ScoreBoard scoreBoard(settings);

  bird.start();
  pipeSpawner.start();
  scoreBoard.start();

  sf::Clock clock;
  GameState gameState = GameState::Playing;

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
        bird.flap();
      }
      else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
      {
        gameState = GameState::Playing;
        bird.start();
        pipeSpawner.start();
        clock.restart();
      }
    }

    if (gameState == GameState::Playing) {
      sf::Time deltaTime = clock.restart();

      bird.update(deltaTime);
      pipeSpawner.update(deltaTime);
      scoreBoard.update(pipeSpawner.getScore());

      if (bird.isColliding(pipeSpawner.getMiddleTopCollisionRect())
        || bird.isColliding(pipeSpawner.getMiddleBottomCollisionRect()))
      {
        gameState = GameState::GameOver;
      }
    }


    window.clear();
    window.draw(background);
    window.draw(bird);
    window.draw(pipeSpawner);
    window.draw(scoreBoard);
    window.display();
  }
}
