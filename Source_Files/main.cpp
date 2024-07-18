#include "SDLAutomata.h"
#include "terminalAutomata.h"
#include <iostream>

int main(int argc, char **argv) {

  std::cout
      << "What version of Cellular Automata do you want to launch?\n"
         "(1) - 1D in terminal.\n"
         "(2) - 2D (Game of life) in terminal (CPU/unoptimized).\n"
         "(3) - 2D (Game of life) using SDL (CPU/unoptimized).\n"
         "(4) - 2D (Game of life) using SDL and OpenGL (GPU/optimized\?\?\?)\n"
         "Enter: ";
  int input;
  while (true) {
    std::cin >> input;
    if (!std::cin.fail() && 1 <= input && input <= 4)
      break;
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cout << "You've entered something wrond. Try again.\n"
                 "Enter:";
  }
  switch (input) {
  case (1):
    terminalAutomata1D();
    break;
  case (2):
    // terminalAutomata2D();
    std::cout << "Not yet. Sorry." << std::endl;
    break;
  case (3): {
    SDLAutomata automataSDL;
    automataSDL.run();
    break;
    }
  case (4): {
    // SDLGLAutomata automataGL;
    // automataGL.run();
    std::cout << "Not yet. Sorry." << std::endl;
    break;
    }
  default:
    std::cout << "Somehow you managed to get here. Now get out..." << std::endl;
  }

  return 0;
}
