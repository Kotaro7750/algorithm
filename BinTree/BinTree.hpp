#include <iostream>

enum ChildDirection { LEFT, RIGHT };

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
  void eraseNode(struct BinTreeNode<T> *node, struct BinTreeNode<T> *parent,
                 ChildDirection Child);
  struct BinTreeNode<T> *LeftMaxParent(struct BinTreeNode<T> *node);
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

template <typename T> bool BinTree<T>::erase(T data) {
  struct BinTreeNode<T> *parentNode = searchParentNode(root, data);
  struct BinTreeNode<T> *deleteNode;

  if (parentNode == nullptr) {
    return false;
  }

  std::cout << parentNode->data << std::endl;

  if (parentNode->LHS != nullptr && parentNode->LHS->data == data) {
    deleteNode = parentNode->LHS;
    std::cout << "deleteNode is " << deleteNode->data << std::endl;
    eraseNode(deleteNode, parentNode, LEFT);
  } else if (parentNode->RHS != nullptr && parentNode->RHS->data == data) {
    deleteNode = parentNode->RHS;
    std::cout << "deleteNode is " << deleteNode->data << std::endl;
    eraseNode(deleteNode, parentNode, RIGHT);
  }

  return true;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::LeftMaxParent(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *tmp = node->LHS;
  while (tmp->RHS != nullptr) {
    if (tmp->RHS->RHS == nullptr) {
      break;
    }
    tmp = tmp->RHS;
  }
  return tmp;
}

template <typename T>
void BinTree<T>::eraseNode(struct BinTreeNode<T> *node,
                           struct BinTreeNode<T> *parent,
                           ChildDirection Child) {
  if (node->LHS == nullptr && node->RHS == nullptr) {
    if (Child == LEFT) {
      parent->LHS = nullptr;
    } else {
      parent->RHS = nullptr;
    }
    delete node;
  } else if (node->LHS == nullptr) {
    if (Child == LEFT) {
      parent->LHS = node->RHS;
    } else {
      parent->RHS = node->RHS;
    }
    delete node;
  } else if (node->RHS == nullptr) {
    if (Child == LEFT) {
      parent->LHS = node->LHS;
    } else {
      parent->RHS = node->LHS;
    }
    delete node;
  } else {
    struct BinTreeNode<T> *leftMaxParent = LeftMaxParent(node);
    node->data = leftMaxParent->RHS->data;
    delete leftMaxParent->RHS;
    leftMaxParent->RHS = nullptr;
  }
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
