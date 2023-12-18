/**
 * @file main.cpp
 * @author Hongming Zhu (zhm1019@qq.com)
 * @brief 程序入口
 * @version 0.1.0
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include "game.h"

/**
 * @brief 程序入口, 读取配置文件, 创建游戏对象, 运行游戏
 */
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
