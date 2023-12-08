#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

#include "game.h"

int main()
{
  nlohmann::json settings;
  std::ifstream settingsFile("settings.json");

  if (!settingsFile.is_open())
  {
    return EXIT_FAILURE;
  }

  settingsFile >> settings;

  ZHMGAME001::Game game(settings);
  
  game.run();

  return EXIT_SUCCESS;
}
