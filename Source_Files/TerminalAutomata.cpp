#include "Automata.h"
#include "my_utils.h"
#include <bitset>
#include <iostream>
#include <string>

void printState(const Automata &au) {
  for (const auto &elem : au.getState())
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

void terminalAutomata() {
  unsigned int size = 61;
  Automata automata = Automata::create(getRuleSet(), std::vector<bool>(size, 0));
  automata.set(size / 2, true);

  for (int i = 0; i < size / 2 + 2; i++) {
    printState(automata);
    automata.newState();
  }
}
