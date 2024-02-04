#include "Automata.h"
#include <cassert>
#include <string>
#include <vector>

Automata Automata::create(std::string &&start_ruleSet,
                          std::vector<bool> &&start_state) {
  return Automata(
      M{.state = std::move(start_state), .ruleSet = std::move(start_ruleSet)});
}

const std::vector<bool> &Automata::getState() const { return m.state; }

void Automata::newState() {
  std::vector<bool> new_state(m.state.size(), false);
  for (int i = 0; i < m.state.size(); i++) {
    bool left = ((i == 0) ? m.state[i] : m.state[i - 1]);
    bool middle = m.state[i];
    bool right = (i == m.state.size() - 1 ? m.state[i] : m.state[i + 1]);
    new_state[i] = calculateState(left, middle, right);
  }
  m.state = std::move(new_state);
}

int Automata::calculateState(int left, int middle, int right) {
  std::string a = std::to_string(left * 100 + middle * 10 + right);
  return m.ruleSet[7 - std::stoull(a, 0, 2)] - '0';
}

void Automata::set(int index, bool value) {
  assert(0 <= index && index < m.state.size() &&
         "Index must be in range [0, state.size() - 1]");
  m.state[index] = value;
}
