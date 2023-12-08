#include <iostream>
#include <random>

#include "pipe.h"


namespace ZHMGAME001 {

const float MAX_HOLE_SIZE = 300.0f;
const float MIN_HOLE_SIZE = 200.0f;
const float PIPE_SPEED = 100.0f;

extern float screenWidth;
extern float screenHeight;

Pipe::Pipe(const nlohmann::json& settings)
{
  if (!texture_.loadFromFile(settings["pipe_img_path"]))
  {
    throw std::runtime_error("Failed to load pipe image");
  }

  topSprite_.setTexture(texture_);
  float scaleX = 0.125f * screenWidth / topSprite_.getGlobalBounds().getSize().x;
  float scaleY = screenHeight / topSprite_.getGlobalBounds().getSize().y;

  topSprite_.setScale(scaleX, scaleY);

  bottomSprite_.setTexture(texture_);
  bottomSprite_.setScale(scaleX, scaleY);
  bottomSprite_.setRotation(180.0f);

  sf::Vector2f pipeSize = topSprite_.getGlobalBounds().getSize();
  topCollisionRect_.setSize(pipeSize);
  topCollisionRect_.setFillColor(sf::Color::Transparent);
  // topCollisionRect_.setOutlineColor(sf::Color::Red);
  // topCollisionRect_.setOutlineThickness(1.0f);

  bottomCollisionRect_.setSize(pipeSize);
  bottomCollisionRect_.setOrigin(pipeSize.x, pipeSize.y);
  bottomCollisionRect_.setFillColor(sf::Color::Transparent);
  // bottomCollisionRect_.setOutlineColor(sf::Color::Red);
  // bottomCollisionRect_.setOutlineThickness(1.0f);
}

void Pipe::start()
{
  std::mt19937 rng(std::random_device{}());

  std::uniform_real_distribution<float> holeSizeDist(MIN_HOLE_SIZE, MAX_HOLE_SIZE);
  float holeSize = holeSizeDist(rng);

  std::uniform_real_distribution<float> holePosDist(holeSize / 2.0f, screenHeight - holeSize / 2.0f);
  float holePos = holePosDist(rng);

  topSprite_.setPosition(screenWidth, holePos - holeSize / 2.0f - topSprite_.getGlobalBounds().height);
  bottomSprite_.setPosition(screenWidth + bottomSprite_.getGlobalBounds().width, holePos + holeSize / 2.0f + bottomSprite_.getGlobalBounds().height);

  topCollisionRect_.setPosition(topSprite_.getPosition());
  bottomCollisionRect_.setPosition(bottomSprite_.getPosition());
}

void Pipe::update(const sf::Time& deltaTime)
{
  sf::Vector2f position = topSprite_.getPosition();
  position.x -= PIPE_SPEED * deltaTime.asSeconds();
  topSprite_.setPosition(position);
  topCollisionRect_.setPosition(position);

  position = bottomSprite_.getPosition();
  position.x -= PIPE_SPEED * deltaTime.asSeconds();
  bottomSprite_.setPosition(position);
  bottomCollisionRect_.setPosition(position);
}

void Pipe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(topSprite_, states);
  target.draw(bottomSprite_, states);
  target.draw(topCollisionRect_, states);
  target.draw(bottomCollisionRect_, states);
}

bool Pipe::isOffScreen() const
{
  return topSprite_.getPosition().x < -topSprite_.getGlobalBounds().width;
}

sf::Vector2f Pipe::getBottomRightPosition() const
{
  return bottomSprite_.getPosition();
}

sf::RectangleShape Pipe::getTopCollisionRect() const
{
  return topCollisionRect_;
}

sf::RectangleShape Pipe::getBottomCollisionRect() const
{
  sf::RectangleShape rect;
  rect.setSize(bottomCollisionRect_.getSize());
  rect.setPosition(bottomCollisionRect_.getPosition() - bottomCollisionRect_.getSize());
  return rect;
}

}  // namespace ZHMGAME001
