#include "Errors.h"

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

void fatalError(std::string errorString) {
  std::cout << errorString << std::endl;
  std::cout << "Enter any key to quit...";
  int temp;
  std::cin >> temp;
  SDL_Quit();
  exit(420);
}

