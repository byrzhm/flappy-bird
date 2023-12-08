#include "pipe_spawner.h"

static float timeSinceLastSpawn = 0.0f;

namespace ZHMGAME001 {

const float SPAWN_RATE = 4.25f;

extern float birdWidth;
extern float screenWidth;
extern float screenHeight;

PipeSpawner::PipeSpawner(const nlohmann::json& settings)
  : settings_(settings)
{}

void PipeSpawner::start()
{
  leftPipes_.clear();
  rightPipes_.clear();

  timeSinceLastSpawn = SPAWN_RATE;  // spawn a pipe immediately
}

void PipeSpawner::update(const sf::Time& deltaTime)
{
  for (auto& pipe : leftPipes_)
  {
    pipe.update(deltaTime);
  }
  for (auto& pipe : rightPipes_)
  {
    pipe.update(deltaTime);
  }

  if (timeSinceLastSpawn > SPAWN_RATE)
  {
    rightPipes_.emplace_back(settings_);
    rightPipes_.back().start();
    timeSinceLastSpawn = 0.0f;
  }
  else
  {
    timeSinceLastSpawn = timeSinceLastSpawn + deltaTime.asSeconds();
  }

  if (!leftPipes_.empty() && leftPipes_.front().isOffScreen())
  {
    leftPipes_.pop_front();
  }

  if (!rightPipes_.empty() && rightPipes_.front().getBottomRightPosition().x < screenWidth / 2.0f - birdWidth / 2.0f)
  {
    scored_ = true;
    auto pipe = rightPipes_.front();
    rightPipes_.pop_front();
    leftPipes_.push_back(std::move(pipe));
  }
}

void PipeSpawner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (const auto& pipe : leftPipes_)
  {
    target.draw(pipe, states);
  }
  for (const auto& pipe : rightPipes_)
  {
    target.draw(pipe, states);
  }
}

sf::RectangleShape PipeSpawner::getMiddleTopCollisionRect() const
{
  if (rightPipes_.empty())
  {
    return sf::RectangleShape();
  }
  return rightPipes_.front().getTopCollisionRect();
}

sf::RectangleShape PipeSpawner::getMiddleBottomCollisionRect() const
{
  if (rightPipes_.empty())
  {
    return sf::RectangleShape();
  }
  return rightPipes_.front().getBottomCollisionRect();
}

bool PipeSpawner::getScored()
{
  bool scored = scored_;
  scored_ = false;
  return scored;
}

}  // namespace ZHMGAME001