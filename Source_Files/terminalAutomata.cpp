#include "terminalAutomata.h"
#include "Automata1D.h"
// #include "Automata2D.h"
#include <bitset>
// #include <chrono>
#include <iostream>
#include <string>
// #include <thread>
#include <vector>

void printState(const Automata1D &au) {
  for (const auto &elem : au.getState())
    std::cout << (!elem ? "\u2588" : "\u2591") << ' ';
  std::cout << std::endl;
}

void printRow(const std::vector<bool> &row) {
  for (const auto &elem : row)
    std::cout << (!elem ? "\u2588" : "\u2591") << ' ';
  std::cout << std::endl;
}

std::string getRuleSet() {
  std::cout << "Enter a rule set you want to display (0 - 255): ";
  int ruleSet = -1;
  while (ruleSet < 0 || ruleSet > 255) {
    std::cin >> ruleSet;
    if (!std::cin.fail())
      continue;
    std::cin.clear();
    std::cin.ignore(32767, '\n');
  }
  std::cout << std::endl;
  return std::bitset<8>(ruleSet).to_string();
}

void terminalAutomata1D() {
  unsigned int size = 61;
  Automata1D automata =
      Automata1D::create(getRuleSet(), std::vector<bool>(size, 0));
  automata.set(size / 2, true);

  for (int i = 0; i < size / 2 + 2; i++) {
    printState(automata);
    automata.newState();
  }
}

// void terminalAutomata2D() {
//   int rows = 24, columns = 24;
//   Automata2D automata = Automata2D::create(
//       3, std::vector<std::vector<bool>>(rows, std::vector(columns, false)));
//   
//   automata.fillRandom();
//
//   for (int i = 0; i < 1000; i++) {
//     system("clear");
//     for (int ind = 0; ind < automata.getState().size(); ind++) {
//       std::cout << ' ';
//       printRow(automata.getState()[ind]);
//     // 700 723
//     }
//     if (i % 10 == 0) automata.newState();
//     std::this_thread::sleep_for(std::chrono::milliseconds(20));
//   }
// }
