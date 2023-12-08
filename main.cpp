#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include "game.h"

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
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
