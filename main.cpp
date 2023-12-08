#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "bird.h"
#include "pipe_spawner.h"

const float GRAVITY = 100.0f;
const float JUMP_VELOCITY = 150.0f;

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

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile(settings["background_img_path"]))
  {
    return EXIT_FAILURE;
  }
  sf::Sprite background(backgroundTexture);
  float scaleX = screenWidth / background.getGlobalBounds().getSize().x;
  float scaleY = screenHeight / background.getGlobalBounds().getSize().y;
  background.setScale(scaleX, scaleY);

  sf::Texture texture;
  if (!texture.loadFromFile(settings["bird_img_path"]))
  {
    return EXIT_FAILURE;
  }

  sf::Sprite bird(texture);
  bird.setScale(0.2f, 0.2f);
  sf::Vector2f birdSize = bird.getGlobalBounds().getSize();
  bird.setPosition((screenWidth - birdSize.x) / 2, (screenHeight - birdSize.y) / 2);

  float velocityY = 0.0f;
  float positionY = bird.getPosition().y;

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
        velocityY = -JUMP_VELOCITY;
      }
    }

    sf::Time deltaTime = clock.restart();
    velocityY = velocityY + GRAVITY * deltaTime.asSeconds();
    positionY = positionY + velocityY * deltaTime.asSeconds();

    if (positionY > screenHeight - birdSize.y)
    {
      positionY = screenHeight - birdSize.y;
      velocityY = 0.0f;
    }
    else if (positionY < 0)
    {
      positionY = 0;
      velocityY = 0.0f;
    }

    bird.setPosition(bird.getPosition().x, positionY);
    // std::cout << bird.getPosition().y << std::endl;

    window.clear();
    window.draw(background);
    window.draw(bird);
    window.display();
  }
}
