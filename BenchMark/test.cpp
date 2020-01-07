#include "BenchMark.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  BenchMark bm;
  bm.Start();
  int j = 0;

  for (int i = 0; i < 10000000; i++) {
    j++;
  }
  bm.Lap();

  for (int i = 0; i < 10000000; i++) {
    j++;
  }
  bm.Lap();

  for (int i = 0; i < 10000000; i++) {
    j++;
  }
  bm.Stop();

  std::cout << bm.getLap(0) << "ms" << bm.getLap(1) << "ms" << bm.getLap(2)
            << "ms";
  return 0;
}
