#include "BinTree.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  BinTree<double> bt(1);
  if (bt.append(6) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(0) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(3) == false) {
    std::cout << "append failed" << std::endl;
  }
  if (bt.append(7) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(2) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(4) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(5) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(-1) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(-2) == false) {
    std::cout << "append failed" << std::endl;
  }

  if (bt.append(-0.9) == false) {
    std::cout << "append failed" << std::endl;
  }

  bt.search(5);
  bt.print();

  if (bt.erase(6) == false) {
    std::cout << "erase failed" << std::endl;
  }

  bt.print();

  if (bt.erase(1) == false) {
    std::cout << "erase failed" << std::endl;
  }

  bt.print();

  return 0;
}
