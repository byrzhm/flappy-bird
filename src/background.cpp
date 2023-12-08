#include "background.h"

namespace ZHMGAME001 {

Backgound::Backgound(const nlohmann::json &settings) {
  float screenWidth = settings["width"];
  float screenHeight = settings["height"];

  if (!texture_.loadFromFile(settings["background_img_path"])) {
    throw std::runtime_error("Failed to load background image");
  }
  sprite_.setTexture(texture_);

  float scaleX = screenWidth / sprite_.getGlobalBounds().getSize().x;
  float scaleY = screenHeight / sprite_.getGlobalBounds().getSize().y;
  sprite_.setScale(scaleX, scaleY);
}

void Backgound::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

} // namespace ZHMGAME001