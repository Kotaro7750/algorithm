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

  struct BinTreeNode<T> *LeftMax(struct BinTreeNode<T> *node);
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
  if (node == nullNode) {
    return node;
  }

  struct BinTreeNode<T> *tmp = node;

  while (tmp != nullNode && tmp->data != data) {
    tmp = data < tmp->data ? tmp->LHS : tmp->RHS;
  }
  return tmp;
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

#define Log(str, x) std::cout << str << x << std::endl;
template <typename T> bool BinTree<T>::erase(T data) {
  struct BinTreeNode<T> *deleteNode = searchNode(root, data);
  struct BinTreeNode<T> *parentNode;
  struct BinTreeNode<T> *junctionNode;

  if (deleteNode == nullNode) {
    return false;
  }

  if (deleteNode == root) {
    eraseNode(deleteNode);
    return true;
  } else {
    parentNode = deleteNode->Parent;
    junctionNode = eraseNode(deleteNode);
    if (data < parentNode->data) {
      parentNode->LHS = junctionNode;
    } else {
      parentNode->RHS = junctionNode;
    }
    return true;
  }
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::eraseNode(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *junctionNode;
  struct BinTreeNode<T> *deleteNode;

  // child num:0
  if (node->LHS == nullNode && node->RHS == nullNode) {
    if (node == root) {
      root = nullNode;
    }
    junctionNode = nullNode;
    deleteNode = node;
  }

  // child num:1
  if ((node->LHS != nullNode && node->RHS == nullNode) ||
      (node->RHS != nullNode && node->LHS == nullNode)) {
    junctionNode = node->LHS == nullNode ? node->RHS : node->LHS;

    if (node == root) {
      root = junctionNode;
    }

    deleteNode = node;
  }

  // child num:2
  if (node->LHS != nullNode && node->RHS != nullNode) {
    struct BinTreeNode<T> *leftMaxNode = LeftMax(node);
    Log("leftMaxNode is:", leftMaxNode->data);

    node->data = leftMaxNode->data;

    // when leftMaxNode is not just a leftNode,
    // RHS of leftMaxNode's parent will be nullNode
    if (node->LHS != leftMaxNode) {
      leftMaxNode->Parent->RHS = nullNode;
    }else {
      node->LHS = eraseNode(leftMaxNode);
    }

    junctionNode = node;
    deleteNode = leftMaxNode;
  }

  delete deleteNode;
  print();
  return junctionNode;
}

template <typename T>
struct BinTreeNode<T> *BinTree<T>::LeftMax(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *leftMaxNode = node->LHS;

  while (leftMaxNode->RHS != nullNode) {
    leftMaxNode = leftMaxNode->RHS;
  }
  return leftMaxNode;
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
  if (root == nullNode) {
    std::cout << "nullNode";
    return;
  }
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
  if (root == nullNode) {
    return true;
  }

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
