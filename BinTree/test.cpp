#include "../BenchMark/BenchMark.hpp"
#include "BinTree.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "./a.out Node_N" << std::endl;
    exit(1);
  }
  int node_n = atoi(argv[1]);

  std::cout << "node_n is " << node_n << std::endl;

  BinTree<int> bt;
  BenchMark bm;

  std::random_device rand;

  int search;
  bm.Start();

  for (int i = 0; i < node_n; i++) {
    search = rand();
    bt.append(search);
  }

  // bt.append(7);
  // bt.append(3);
  // bt.append(6);
  // bt.append(6);
  // bt.append(8);
  // bt.append(1);
  // bt.append(2);
  // bt.append(9);

  long appendT = bm.Lap();
  std::cout << "append time:" << bm.getLap(appendT) << "[ms]" << std::endl;
  // bt.graph();
  assert(bt.checkAVL());
  assert(bt.checkBin());

  // bt.RotateTest(0);

  return 0;
}
