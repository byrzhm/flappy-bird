#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "bird.h"

static float screenWidth = 0.0f;
static float screenHeight = 0.0f; 
static float maxHeight = 0.0f;

namespace ZHMGAME001 {
const float GRAVITY = 100.0f;
const float JUMP_VELOCITY = 80.0f;
float birdWidth = 0.0f;
float birdHeight = 0.0f;

Bird::Bird(const nlohmann::json &settings) {
  screenWidth = settings["width"];
  screenHeight = settings["height"];

  if (!texture_.loadFromFile(settings["bird_img_path"])) {
    throw std::runtime_error("Failed to load bird image");
  }

  sprite_.setTexture(texture_);
  sprite_.setScale(0.2f, 0.2f);
  sf::Vector2f birdSize = sprite_.getGlobalBounds().getSize();
  birdWidth = birdSize.x;
  birdHeight = birdSize.y;
  
  maxHeight = screenHeight - birdSize.y;

  collisionCircle_.setRadius(birdSize.x / 2);
  collisionCircle_.setOrigin(collisionCircle_.getRadius(), collisionCircle_.getRadius());
  collisionCircle_.setFillColor(sf::Color::Transparent);
  collisionCircle_.setOutlineColor(sf::Color::Red);
  collisionCircle_.setOutlineThickness(1.0f);
}

void Bird::start() {
  sprite_.setPosition((screenWidth - birdWidth) / 2,
                      (screenHeight - birdHeight) / 2);
  collisionCircle_.setPosition(getCenter());

  velocity_ = sf::Vector2f(0.0f, 0.0f);
}

void Bird::update(const sf::Time &deltaTime) {
  velocity_.y += GRAVITY * deltaTime.asSeconds();
  float positionY = sprite_.getPosition().y + velocity_.y * deltaTime.asSeconds();
  if (positionY > maxHeight) {
    positionY = maxHeight;
    velocity_.y = 0.0f;
  } else if (positionY < 0.0f) {
    positionY = 0.0f;
    velocity_.y = 0.0f;
  }
  sprite_.setPosition(sprite_.getPosition().x, positionY);
  collisionCircle_.setPosition(getCenter());
}

void Bird::flap() { 
  if (velocity_.y < 0.0f && velocity_.y < - 2.0f * JUMP_VELOCITY) {
    velocity_.y += velocity_.y/2.0f;
  } else {
    velocity_.y = -JUMP_VELOCITY;
  }
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite_, states);
  target.draw(collisionCircle_, states);
}

sf::Vector2f Bird::getCenter() const {
  sf::Vector2f birdSize = sprite_.getGlobalBounds().getSize();
  return sprite_.getPosition() + sf::Vector2f{birdSize.x / 2 - 1.0f, birdSize.y / 2 + 9.0f};
}

bool Bird::isColliding(const sf::RectangleShape &rect) const {
  if (rect.getSize() == sf::Vector2f(0.0f, 0.0f)) {
    return false;
  }

  sf::Vector2f rectSize = rect.getSize();
  sf::Vector2f rectPosition = rect.getPosition();
  sf::Vector2f birdCenter = getCenter();
  float birdRadius = collisionCircle_.getRadius();

  glm::vec2 center(birdCenter.x, birdCenter.y);
  glm::vec2 rect_half_extents(rectSize.x / 2, rectSize.y / 2);
  glm::vec2 rect_center(
    rectPosition.x + rect_half_extents.x,
    rectPosition.y + rect_half_extents.y
  );

  glm::vec2 difference = center - rect_center;
  glm::vec2 clamped = glm::clamp(difference, -rect_half_extents, rect_half_extents);
  glm::vec2 closest = rect_center + clamped;
  difference = closest - center;

  return glm::length(difference) < birdRadius;
}

} // namespace ZHMGAME001