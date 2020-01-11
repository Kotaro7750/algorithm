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

  // std::cout << "node_n is " << node_n << std::endl;
  std::cout << node_n << ",";

  BinTree<int> bt;
  BenchMark bm;

  std::random_device rand;

  int search;
  bm.Start();

  for (int i = 0; i < node_n; i++) {
    search = (int)rand();
    bt.append(search);
  }

  long appendT = bm.Lap();
  // std::cout << "append time:" << bm.getLap(appendT) << "[ms]" << std::endl;
  std::cout << bm.getLap(appendT) << ",";
  assert(bt.checkAVL());
  assert(bt.checkBin());

  bm.Lap();

  for (int i = 0; i < node_n / 1000; i++) {
    search = (int)rand();
    bt.append(search);
  }
  long appendAVG = bm.Lap();
  std::cout << bm.getLapNS(appendAVG) / (node_n / 1000) << std::endl;

  // for (int i = 0; i < node_n; i++) {
  //  search = (int)rand();
  //  bt.erase(search);
  //}
  // long eraseT = bm.Lap();

  //// std::cout << "erase time:" << bm.getLap(eraseT) << "[ms]" << std::endl;
  // std::cout << bm.getLap(eraseT) << std::endl;
  // assert(bt.checkAVL());
  // assert(bt.checkBin());

  return 0;
}
