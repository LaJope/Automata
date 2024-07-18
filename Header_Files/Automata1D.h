#pragma once
#include <string>
#include <vector>

class Automata1D {
private:
  struct M {
    std::string ruleSet;
    std::vector<bool> state;
  } m;
  explicit Automata1D(M new_m) : m(std::move(new_m)) {}
  int calculateState(int left, int middle, int right);

public:
  static Automata1D create(std::string &&start_ruleSet = "00000000",
                         std::vector<bool> &&start_state = {0});
  void newState();
  void set(int index, bool value);
  const std::vector<bool> &getState() const;
};
