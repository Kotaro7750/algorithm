#include "../BenchMark/BenchMark.hpp"
#include "BinTree.hpp"
#include <chrono>
#include <iostream>
#include <random>

#define MAX 1000000

int main(int argc, char const *argv[]) {
  BinTree<int> bt(1);
  BenchMark bm;

  std::random_device rand;

  int search;
  bm.Start();
  for (int i = 0; i < MAX; i++) {
    search = rand();
    bt.append(search);
  }
  bt.append(1);
  long appendT = bm.Lap();

  std::cout << "append time:" << bm.getLap(appendT) << "[ms]" << std::endl;

  bt.search(search);

  return 0;
}
