#include <memory>

#include "bird.h"
#include "pipe_spawner.h"
#include "score_board.h"
#include "background.h"

namespace ZHMGAME001 {

enum class GameState {
  PLAYING,
  GAME_OVER
};

class Game : public sf::Drawable{
public:
  Game() = delete;
  explicit Game(const nlohmann::json& settings);

  void run();

private:
  void start();

  void update(const sf::Time& deltaTime);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void reset();

  GameState getGameState() const;

private:
  std::unique_ptr<Bird> bird_;
  std::unique_ptr<PipeSpawner> pipeSpawner_;
  std::unique_ptr<ScoreBoard> scoreBoard_;
  std::unique_ptr<Background> background_;
  const nlohmann::json& settings_;
  GameState gameState_{GameState::PLAYING};
};
} // namespace ZHMGAME001