#include "Automata2D.h"
#include "Random.h"
#include <cassert>
#include <vector>

Automata2D Automata2D::create(int start_rule,
                              std::vector<std::vector<bool>> &&start_field) {
  return Automata2D(M{.rule = start_rule, .field = std::move(start_field)});
}

Automata2D Automata2D::create(int start_rule, int rows, int columns) {
  return create(start_rule, std::vector<std::vector<bool>>(
                                rows, std::vector<bool>(columns, false)));
}

void Automata2D::newState() {
  std::vector<std::vector<bool>> new_field(
      m.field.size(), std::vector(m.field[0].size(), false));
  for (int row = 0; row < new_field.size(); row++)
    for (int column = 0; column < new_field[0].size(); column++) {
      int lt = m.field[(row - 1 + m.field.size()) % m.field.size()]
                      [(column - 1 + m.field[0].size()) % m.field[0].size()];
      int t = m.field[(row - 1 + m.field.size()) % m.field.size()][column];
      int rt = m.field[(row - 1 + m.field.size()) % m.field.size()]
                      [(column + 1) % m.field[0].size()];

      int lc =
          m.field[row][(column - 1 + m.field[0].size()) % m.field[0].size()];
      int rc = m.field[row][(column + 1) % m.field[0].size()];

      int lb = m.field[(row + 1) % m.field.size()]
                      [(column - 1 + m.field[0].size()) % m.field[0].size()];
      int b = m.field[(row + 1) % m.field.size()][column % m.field[0].size()];
      int rb =
          m.field[(row + 1) % m.field.size()][(column + 1) % m.field[0].size()];
      int sum = lt + t + rt + lc + rc + lb + b + rb;
      if (m.field[row][column])
        new_field[row][column] = (sum == 2 || sum == 3);
      else
        new_field[row][column] = (sum == 3);
    }
  m.field = std::move(new_field);
}

void Automata2D::set(int row, int column, bool value) {
  assert(row >= 0 && row <= m.field.size() && column >= 0 &&
         column <= m.field[0].size());
  m.field[row][column] = value;
}

void Automata2D::fillRandom() {
  for (int i = 0; i < getRandomNum(getNumRows() * getNumColumns() * 1 / 10,
                                    getNumRows() * getNumColumns() * 3 / 10);
       i++)
    set(getRandomNum(0, getNumRows() - 1),
        getRandomNum(0, getNumColumns() - 1), true);
}

const int Automata2D::getNumRows() const { return m.field.size(); }
const int Automata2D::getNumColumns() const { return m.field[0].size(); }

const bool Automata2D::getState(int row, int col) const {
  return m.field[row][col];
}
