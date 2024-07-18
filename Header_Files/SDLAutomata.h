#pragma once
// #include "Automata2D.h"
#include "Automata2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

enum class AutomataState { RUN, EXIT };

class SDLAutomata {
private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  int _screenWidth;
  int _screenHeight;
  AutomataState _automataState;
  Automata2D _automata;

  void initSystems();
  void automataLoop();
  void processInput();
  void drawAutomata();

public:
  SDLAutomata();
  ~SDLAutomata();

  void run();
};
