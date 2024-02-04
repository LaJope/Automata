#pragma once
#include "my_utils.h"
#include <string>
#include <vector>

class Automata {
private:
  struct M {
    std::vector<bool> state;
    std::string ruleSet;
  } m;
  explicit Automata(M new_m) : m(std::move(new_m)) {}

  int calculateState(int left, int middle, int right);

public:
  static Automata create(std::string &&start_ruleSet = "00000000",
                         std::vector<bool> &&start_state = {0});
  const std::vector<bool> &getState() const;
  void newState();

  void set(int index, bool value);

  friend void terminalAutomata();
};
