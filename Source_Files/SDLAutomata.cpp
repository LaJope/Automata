#include "SDLAutomata.h"
#include "Automata2D.h"
#include "Errors.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

SDLAutomata::SDLAutomata()
    : _window(nullptr), _screenWidth(1000), _screenHeight(1000),
      _automataState(AutomataState::RUN),
      _automata(Automata2D::create(3, 200, 200)) {}
SDLAutomata::~SDLAutomata() {}

void SDLAutomata::initSystems() {
  SDL_Init(SDL_INIT_EVERYTHING);

  _window = SDL_CreateWindow("Cellular Automata", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, _screenWidth,
                             _screenHeight, SDL_WINDOW_OPENGL);
  if (_window == nullptr)
    fatalError("SDL Window could not be created!");

  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == nullptr)
    fatalError("SDL Renderer could not be created!");

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (glContext == nullptr)
    fatalError("SDL_GL Context could not be created!");

  GLenum error = glewInit();
  if (error != GLEW_OK)
    fatalError("Could not initialize Glew!");

  _automata.fillRandom();

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// void SDLAutomata::automataLoop() {
//   while (_automataState != AutomataState::EXIT) {
//     processInput();
//     _automata.newState();
//     drawAutomata();
//     // std::this_thread::sleep_for(std::chrono::milliseconds(200));
//   }
// }

void SDLAutomata::automataLoop() {
  while (_automataState != AutomataState::EXIT) {
    // Measure processing time of _automata.newState()
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    start = std::chrono::high_resolution_clock::now();
    _automata.newState();
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::nano> processingTime = end - start;

    // Calculate remaining delay after accounting for processing time
    double desiredDelay = 0.3;
    double remainingDelay =
        std::clamp(desiredDelay - processingTime.count() / 1'000'000'000,
                   desiredDelay - 0.1, // Minimum allowed delay
                   desiredDelay + 0.1  // Maximum allowed delay
        );
    // std::cout << remainingDelay << std::endl;

    processInput();

    std::this_thread::sleep_for(std::chrono::duration<double>(remainingDelay));

    // Draw the automata
    drawAutomata();
  }
}

void SDLAutomata::processInput() {
  SDL_Event evnt;

  while (SDL_PollEvent(&evnt)) {
    switch (evnt.type) {
    case SDL_QUIT:
      _automataState = AutomataState::EXIT;
      return;
    case SDL_WINDOWEVENT_RESIZED:
      _screenWidth = evnt.window.data1;
      _screenHeight = evnt.window.data2;
    }
  }
}

void SDLAutomata::drawAutomata() {
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SDL_Rect background;
  background.w = _screenWidth;
  background.h = _screenHeight;
  background.x = 0;
  background.y = 0;
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(_renderer, &background);

  int startPos = 0;
  for (int y = 0; y < _automata.getNumColumns(); y++) {
    for (int x = 0; x < _automata.getNumRows(); x++) {
      if (_automata.getState(x, y)) {
        SDL_Rect cell;
        cell.w = _screenWidth / _automata.getNumColumns();
        cell.h = _screenHeight / _automata.getNumRows();
        cell.x = x * cell.w + 1;
        cell.y = y * cell.h + 1;
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(_renderer, &cell);
      }
    }
  }
  SDL_RenderPresent(_renderer);

  SDL_GL_SwapWindow(_window);
}

void SDLAutomata::run() {
  initSystems();
  automataLoop();
}
