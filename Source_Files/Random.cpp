#include "Random.h"
#include <random>

int getRandomNum(int min, int max) {
  static std::random_device rd;
  static std::mt19937 mersenne(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(mersenne);
}
