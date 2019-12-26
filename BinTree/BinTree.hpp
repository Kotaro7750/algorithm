#include <iostream>

template <typename T> struct BinTreeNode {
  T data;
  struct BinTreeNode<T> *LHS;
  struct BinTreeNode<T> *RHS;
};

template <typename T> class BinTree {
public:
  BinTree(T);
  BinTreeNode<T> *getRoot();
  bool search(T data);
  bool append(T data);
  bool erase(T data);
  void print();

private:
  struct BinTreeNode<T> *root;
  BinTreeNode<T> *searchNode(struct BinTreeNode<T> *node, T data);
  BinTreeNode<T> *searchParentNode(struct BinTreeNode<T> *node, T data);
  void printRec(struct BinTreeNode<T> *node);
};

// Constructor
template <typename T> inline BinTree<T>::BinTree(T initdata) {
  root = new struct BinTreeNode<T>;

  root->data = initdata;
  root->LHS = nullptr;
  root->RHS = nullptr;
}

// getter
template <typename T> inline BinTreeNode<T> *BinTree<T>::getRoot() {
  return root;
}

template <typename T> bool BinTree<T>::search(T data) {
  struct BinTreeNode<T> *result = searchNode(root, data);
  if (result == nullptr) {
    return false;
  }

  return true;
}

template <typename T>
BinTreeNode<T> *BinTree<T>::searchNode(struct BinTreeNode<T> *node, T data) {
  if (node == nullptr || node->data == data) {
    return node;
  }

  struct BinTreeNode<T> *searchNode = data < node->data ? node->LHS : node->RHS;
  if (searchNode == nullptr) {
    return nullptr;
  }
  return BinTree<T>::searchNode(searchNode, data);
}

template <typename T> bool BinTree<T>::append(T data) {
  struct BinTreeNode<T> *parent = searchParentNode(root, data);

  if (data < parent->data) {
    if (parent->LHS != nullptr) {
      return false;
    }
  } else {
    if (parent->RHS != nullptr) {
      return false;
    }
  }

  struct BinTreeNode<T> *newNode = new struct BinTreeNode<T>;
  newNode->data = data;
  newNode->LHS = nullptr;
  newNode->RHS = nullptr;

  if (data < parent->data) {
    parent->LHS = newNode;
  } else {
    parent->RHS = newNode;
  }

  return true;
}

// return parent node's pointer whose child will have "data".
template <typename T>
BinTreeNode<T> *BinTree<T>::searchParentNode(struct BinTreeNode<T> *node,
                                             T data) {
  struct BinTreeNode<T> *searchNode = data < node->data ? node->LHS : node->RHS;
  if (searchNode == nullptr || searchNode->data == data) {
    return node;
  }
  return BinTree<T>::searchParentNode(searchNode, data);
}

// bug
template <typename T> bool BinTree<T>::erase(T data) {
  struct BinTreeNode<T> *parentNode = searchParentNode(root, data);
  struct BinTreeNode<T> *deleteNode;

  if (parentNode == nullptr) {
    return false;
  }

  if (parentNode->LHS->data == data) {
    deleteNode = parentNode->LHS;
    parentNode->LHS == nullptr;
  } else {
    deleteNode = parentNode->RHS;
    parentNode->RHS == nullptr;
  }

  delete deleteNode;
  return true;
}

template <typename T> void BinTree<T>::print() {
  printRec(root);
  std::cout << std::endl;
}

template <typename T> void BinTree<T>::printRec(struct BinTreeNode<T> *node) {
  if (node->LHS == nullptr && node->RHS == nullptr) {
    std::cout << node->data;
    return;
  }

  std::cout << node->data << " {";
  if (node->LHS != nullptr) {
    std::cout << "L:";
    printRec(node->LHS);

    if (node->RHS != nullptr) {
      std::cout << ",";
    }
  }
  if (node->RHS != nullptr) {
    std::cout << "R:";
    printRec(node->RHS);
  }
  std::cout << "}";
}
