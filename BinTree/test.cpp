#include "../BenchMark/BenchMark.hpp"
#include "BinTree.hpp"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#define FILENAME "rand.csv"

bool genRand(int node_n) {
  std::ofstream ofs(FILENAME);
  if (ofs.fail()) {
    return false;
  }

  std::random_device rand;

  for (int i = 0; i < node_n; i++) {
    ofs << rand() << std::endl;
  }

  return true;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "./a.out Node_N" << std::endl;
    exit(1);
  }
  int node_n = atoi(argv[1]);

  std::cout << "node_n is " << node_n << std::endl;

  if (genRand(node_n) == false) {
    std::cerr << "cannot generate rand" << std::endl;
    exit(1);
  }

  std::vector<int> rand;

  char buf[256];

  std::ifstream ifs(FILENAME);
  if (ifs.fail()) {
    std::cerr << "cannot open file" << std::endl;
    exit(1);
  }
  while (ifs.getline(buf, 256 - 1)) {
    rand.push_back(atoi(buf));
  }

  std::cout << rand.size() << std::endl;

  BinTree<int> bt;
  BenchMark bm;

  int search;
  bm.Start();

  for (int i = 0; i < node_n; i++) {
    search = rand[i];
    bt.append(search);
  }

  long appendT = bm.Lap();
  std::cout << "append time:" << bm.getLap(appendT) << "[ms]" << std::endl;
  assert(bt.checkAVL());
  assert(bt.checkBin());

  bm.Lap();

  for (int i = 0; i < node_n; i++) {
    search = rand[i];
    bt.erase(search);
  }
  long eraseT = bm.Lap();

  std::cout << "erase time:" << bm.getLap(eraseT) << "[ms]" << std::endl;
  assert(bt.checkAVL());
  assert(bt.checkBin());

  return 0;
}
