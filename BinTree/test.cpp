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

  // for (int i = 0; i < node_n; i++) {
  //  search = rand() % 10;
  //  bt.append(search);
  //}

  bt.append(100);
  bt.append(-1);
  bt.append(0);
  bt.append(-5);
  bt.append(-3);
  bt.append(-6);
  bt.append(-2);
  bt.append(-4);

  long appendT = bm.Lap();
  std::cout << "append time:" << bm.getLap(appendT) << "[ms]" << std::endl;
  bt.graph();
  assert(bt.checkBin());

  bt.RotateTest(0);

  assert(bt.checkBin());
  bt.graph();

  return 0;
}
