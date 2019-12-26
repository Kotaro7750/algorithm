#include "BinTree.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  BinTree<int> bt(1);
  if (bt.append(2) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(0) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(5) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(4) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(-1) == false) {
    std::cout << "append failed" << std::endl;
  }

  bt.search(5);
  bt.print();

  return 0;
}
