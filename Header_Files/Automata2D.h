#pragma once
#include <vector>

class Automata2D {
private:
  struct M {
    int rule;
    std::vector<std::vector<bool>> field;
  } m;
  explicit Automata2D(M new_m) : m(std::move(new_m)) {}

public:
  static Automata2D create(int start_rule = 3,
                         std::vector<std::vector<bool>> &&start_field = {{false}});
  static Automata2D create(int start_rule = 3, int rows = 1, int columns = 1);
  void newState();
  void set(int row, int column, bool value);
  void fillRandom();
  const int getNumRows() const;
  const int getNumColumns() const;
  const bool getState(int row, int col) const;

  friend void terminalAutomata2D();
};

