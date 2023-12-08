#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

namespace ZHMGAME001 {

class ScoreBoard : public sf::Drawable {
public:
  ScoreBoard() = default;
  explicit ScoreBoard(const nlohmann::json &settings);

  void start();

  void update(bool scored);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
  void incrementScore();

private:
  sf::Font font_;
  sf::Text scoreText_;
  int score_{0};
};

} // namespace ZHMGAME001