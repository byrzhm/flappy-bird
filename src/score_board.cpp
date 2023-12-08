#include "score_board.h"

namespace ZHMGAME001 {

extern float screenWidth;
extern float screenHeight;

ScoreBoard::ScoreBoard(const nlohmann::json& settings) {
  font_.loadFromFile(settings["font"]);
  scoreText_.setFont(font_);
  scoreText_.setCharacterSize(50);
  scoreText_.setFillColor(sf::Color::White);
  scoreText_.setOutlineColor(sf::Color::Black);
  scoreText_.setOutlineThickness(2.0f);
  scoreText_.setPosition(20.0f, 50.0f);
}

void ScoreBoard::start() {
  score_ = 0;
  scoreText_.setString(std::to_string(score_));
}

void ScoreBoard::update(bool scored) {
  if (!scored) {
    return;
  }
  incrementScore();
  scoreText_.setString(std::to_string(score_));
}

void ScoreBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(scoreText_, states);
}

void ScoreBoard::incrementScore() {
  score_++;
}

} // namespace ZHMGAME001
