#include "BinTree.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  BinTree<int> bt(1);
  bt.append(6);
  bt.append(0);
  bt.append(5);
  bt.append(7);

  bt.search(5);
  bt.print();

  bt.RotateTest(6);

  bt.print();

  return 0;
}
