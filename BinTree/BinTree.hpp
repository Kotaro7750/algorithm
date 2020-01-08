#include <iostream>
#include <queue>

enum ChildDirection { LEFT, RIGHT };

template <typename T> struct BinTreeNode {
  T data;
  struct BinTreeNode<T> *Parent;
  struct BinTreeNode<T> *LHS;
  struct BinTreeNode<T> *RHS;
  int height;
};

template <typename T> class BinTree {
public:
  BinTree();
  ~BinTree();
  BinTreeNode<T> *getRoot();
  bool search(T data);
  bool append(T data);
  bool erase(T data);
  void print();
  void RotateTest(T data);
  bool checkBin();
  bool checkAVL();

private:
  struct BinTreeNode<T> *root;
  struct BinTreeNode<T> *nullNode;

  int bias(struct BinTreeNode<T> *node);
  void modHeight(struct BinTreeNode<T> *node);

  BinTreeNode<T> *searchNode(struct BinTreeNode<T> *node, T data);
  BinTreeNode<T> *searchParentNode(struct BinTreeNode<T> *node, T data);

  BinTreeNode<T> *eraseNode(struct BinTreeNode<T> *node);

  struct BinTreeNode<T> *LeftMaxParent(struct BinTreeNode<T> *node);
  struct BinTreeNode<T> *RotateRight(struct BinTreeNode<T> *node);
  struct BinTreeNode<T> *RotateLeft(struct BinTreeNode<T> *node);

  void printRec(struct BinTreeNode<T> *node);
};

template <typename T> inline BinTree<T>::BinTree() {
  nullNode = new struct BinTreeNode<T>;
  nullNode->LHS = nullptr;
  nullNode->RHS = nullptr;
  nullNode->Parent = nullptr;
  nullNode->height = 0;

  root = nullNode;
}

template <typename T> BinTree<T>::~BinTree<T>() {
  std::queue<struct BinTreeNode<T> *> queue;

  if (root == nullNode) {
    delete nullNode;
    return;
  }

  if (root->LHS != nullNode) {
    queue.push(root->LHS);
  }
  if (root->RHS != nullNode) {
    queue.push(root->RHS);
  }

  while (!queue.empty()) {
    struct BinTreeNode<T> *front = queue.front();
    queue.pop();

    if (front->LHS != nullNode) {
      queue.push(front->LHS);
    }
    if (front->RHS != nullNode) {
      queue.push(front->RHS);
    }

    delete front;
  }
  delete nullNode;
  delete root;
}

// getter
template <typename T> inline BinTreeNode<T> *BinTree<T>::getRoot() {
  return root;
}

//--------------------
// utility
//--------------------

// node must not nullNode
template <typename T> inline int BinTree<T>::bias(struct BinTreeNode<T> *node) {
  return node->LHS->height - node->RHS->height;
}

template <typename T> inline void modHeight(struct BinTreeNode<T> *node) {
  node->height =
      1 + (node->LHS->height > node->RHS->height ? node->LHS->height
                                                 : node->RHS->height);
}
//--------------------
// search
//--------------------
template <typename T> bool BinTree<T>::search(T data) {
  struct BinTreeNode<T> *result = searchNode(root, data);

  if (result == nullNode) {
    return false;
  }

  return true;
}

template <typename T>
BinTreeNode<T> *BinTree<T>::searchNode(struct BinTreeNode<T> *node, T data) {
  if (node == nullNode || node->data == data) {
    return node;
  }

  struct BinTreeNode<T> *searchNode = data < node->data ? node->LHS : node->RHS;
  if (searchNode == nullNode) {
    return nullNode;
  }
  return BinTree<T>::searchNode(searchNode, data);
}

//--------------------
// append
//--------------------
template <typename T> bool BinTree<T>::append(T data) {
  // initial append
  if (root == nullNode) {
    struct BinTreeNode<T> *newNode = new struct BinTreeNode<T>;
    newNode->data = data;
    newNode->Parent = nullNode;
    newNode->LHS = nullNode;
    newNode->RHS = nullNode;
    newNode->height = 1;

    root = newNode;
    return true;
  }

  struct BinTreeNode<T> *parent = searchParentNode(root, data);

  if (parent->data == data) {
    return false;
  }

  if (data < parent->data) {
    if (parent->LHS != nullNode) {
      return false;
    }
  } else {
    if (parent->RHS != nullNode) {
      return false;
    }
  }

  struct BinTreeNode<T> *newNode = new struct BinTreeNode<T>;
  newNode->data = data;
  newNode->Parent = parent;
  newNode->LHS = nullNode;
  newNode->RHS = nullNode;
  newNode->height = 1;

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
  // if node is root or nullNode,return themself.
  if (node->data == data || node == nullNode) {
    return node;
  }

  struct BinTreeNode<T> *parent = node;
  struct BinTreeNode<T> *canditate = data < node->data ? node->LHS : node->RHS;

  while (canditate != nullNode && canditate->data != data) {
    parent = canditate;
    canditate = data < canditate->data ? canditate->LHS : canditate->RHS;
  }

  return parent;
}

//--------------------
// erase
//--------------------
template <typename T> bool BinTree<T>::erase(T data) {
  struct BinTreeNode<T> *parentNode = searchParentNode(root, data);
  struct BinTreeNode<T> *deleteNode;
  struct BinTreeNode<T> *junctionNode;

  if (root->data == data) {
    deleteNode = root;
    junctionNode = eraseNode(deleteNode);
    root = junctionNode;

    return true;
  }

  if (parentNode == nullptr) {
    return false;
  }

  if (parentNode->LHS != nullptr && parentNode->LHS->data == data) {
    deleteNode = parentNode->LHS;
    junctionNode = eraseNode(deleteNode);
    parentNode->LHS = junctionNode;

  } else if (parentNode->RHS != nullptr && parentNode->RHS->data == data) {
    deleteNode = parentNode->RHS;
    junctionNode = eraseNode(deleteNode);
    parentNode->RHS = junctionNode;
  }

  return true;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::eraseNode(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *ret;
  struct BinTreeNode<T> *deleteNode;

  if (node->LHS == nullptr && node->RHS == nullptr) {
    ret = nullptr;
    deleteNode = node;

  } else if (node->LHS == nullptr) {
    ret = node->RHS;
    deleteNode = node;

  } else if (node->RHS == nullptr) {
    ret = node->LHS;
    deleteNode = node;

  } else {
    struct BinTreeNode<T> *leftMaxParent = LeftMaxParent(node);

    // when erase root,root->LHS will be root
    if (leftMaxParent == root->LHS) {
      root->LHS->RHS = root->RHS;
      ret = root->LHS;
      deleteNode = root;

    } else {
      node->data = leftMaxParent->RHS->data;
      deleteNode = leftMaxParent->RHS;
      leftMaxParent->RHS = nullptr;
      ret = node;
    }
  }

  delete deleteNode;
  return ret;
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

//--------------------
// rotate
//--------------------
template <typename T>
void BinTree<T>::RotateTest(T data) {
  struct BinTreeNode<T> *parent = searchParentNode(root, data);
  struct BinTreeNode<T> *junctionNode;

  if (parent->LHS != nullptr && parent->LHS->data == data) {
    junctionNode = RotateRight(parent->LHS);
    parent->LHS = junctionNode;
  } else if (parent->RHS != nullptr && parent->RHS->data == data) {
    junctionNode = RotateRight(parent->RHS);
    parent->RHS = junctionNode;
  }

  return;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateRight(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *X = node->LHS->LHS;
  struct BinTreeNode<T> *Y = node->LHS->RHS;
  struct BinTreeNode<T> *Z = node->RHS;

  struct BinTreeNode<T> *partitionRoot = node->LHS;

  node->LHS = Y;
  partitionRoot->RHS = node;

  return partitionRoot;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateLeft(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *X = node->LHS;
  struct BinTreeNode<T> *Y = node->RHS->LHS;
  struct BinTreeNode<T> *Z = node->RHS;

  struct BinTreeNode<T> *partitionRoot = node->RHS;

  node->RHS = Y;
  partitionRoot->LHS = node;

  return partitionRoot;
}

//--------------------
// debug
//--------------------
template <typename T>
void BinTree<T>::print() {
  printRec(root);
  std::cout << std::endl;
}

template <typename T> void BinTree<T>::printRec(struct BinTreeNode<T> *node) {
  if (node->LHS == nullNode && node->RHS == nullNode) {
    std::cout << node->data;
    return;
  }

  std::cout << node->data << " {";
  if (node->LHS != nullNode) {
    std::cout << "L:";
    printRec(node->LHS);

    if (node->RHS != nullNode) {
      std::cout << ",";
    }
  }
  if (node->RHS != nullNode) {
    std::cout << "R:";
    printRec(node->RHS);
  }
  std::cout << "}";
}

template <typename T> bool BinTree<T>::checkBin() {
  std::queue<struct BinTreeNode<T> *> queue;
  queue.push(root);

  while (!queue.empty()) {
    struct BinTreeNode<T> *tmp = queue.front();
    queue.pop();
    T left = tmp->LHS == nullNode ? tmp->data - 1 : tmp->LHS->data;
    T right = tmp->RHS == nullNode ? tmp->data + 1 : tmp->RHS->data;

    if (tmp->data <= left || right <= tmp->data) {
      return false;
    }

    if (tmp->LHS != nullNode) {
      queue.push(tmp->LHS);
    }

    if (tmp->RHS != nullNode) {
      queue.push(tmp->RHS);
    }
  }
  return true;
}

template <typename T> bool BinTree<T>::checkAVL() {
  std::queue<struct BinTreeNode<T> *> queue;
  queue.push(root);
  while (!queue.empty()) {
    struct BinTreeNode<T> *tmp = queue.front();
    queue.pop();

    int bias = bias(tmp);

    if (bias <= -2 || 2 <= bias) {
      return false;
    }

    if (tmp->LHS != nullNode) {
      queue.push(tmp->LHS);
    }

    if (tmp->RHS != nullNode) {
      queue.push(tmp->RHS);
    }
  }
  return true;
}
