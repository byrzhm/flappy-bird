#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <deque>

#include "pipe.h"

namespace ZHMGAME001 {

class PipeSpawner : public sf::Drawable {
public:
  PipeSpawner() = delete;
  explicit PipeSpawner(const nlohmann::json &settings);

  void start();

  void update(const sf::Time &deltaTime);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  sf::RectangleShape getMiddleTopCollisionRect() const;

  sf::RectangleShape getMiddleBottomCollisionRect() const;

  bool getScore();

private:
  std::deque<Pipe> leftPipes_;
  std::deque<Pipe> rightPipes_;
  const nlohmann::json &settings_;
  bool scored_{false};
};

} // namespace ZHMGAME001