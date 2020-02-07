#include <fstream>
#include <iostream>
#include <queue>

template <typename T> struct BinTreeNode {
  T data;
  struct BinTreeNode<T> *Parent;
  struct BinTreeNode<T> *LHS;
  struct BinTreeNode<T> *RHS;
  int height;
  int bias;
};

template <typename T> class BinTree {
public:
  BinTree();
  ~BinTree();

  BinTreeNode<T> *getRoot();
  bool search(T data);
  bool append(T data);
  bool erase(T data);
  void graph();
  void animation(std::string dir);
  void graphDebug();
  bool checkBin();
  bool checkAVL();

private:
  struct BinTreeNode<T> *root;
  struct BinTreeNode<T> *nullNode;
  int animationCount;

  int bias(struct BinTreeNode<T> *node);
  void modHeight(struct BinTreeNode<T> *node);

  BinTreeNode<T> *searchNode(struct BinTreeNode<T> *node, T data);
  BinTreeNode<T> *searchParentNode(struct BinTreeNode<T> *node, T data);

  struct BinTreeNode<T> *LeftMax(struct BinTreeNode<T> *node);

  void Replace(struct BinTreeNode<T> *before, struct BinTreeNode<T> *after);

  struct BinTreeNode<T> *RotateR(struct BinTreeNode<T> *node);
  struct BinTreeNode<T> *RotateL(struct BinTreeNode<T> *node);
  struct BinTreeNode<T> *RotateRL(struct BinTreeNode<T> *node);
  struct BinTreeNode<T> *RotateLR(struct BinTreeNode<T> *node);

  void ToDot();

  void BalanceA(struct BinTreeNode<T> *node);
  void BalanceE(struct BinTreeNode<T> *node);

  void DumpNode(struct BinTreeNode<T> *node);
};

template <typename T> inline BinTree<T>::BinTree() {
  nullNode = new struct BinTreeNode<T>;
  nullNode->LHS = nullptr;
  nullNode->RHS = nullptr;
  nullNode->Parent = nullptr;
  nullNode->height = 0;

  root = nullNode;

  animationCount = 0;
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

template <typename T>
inline void BinTree<T>::modHeight(struct BinTreeNode<T> *node) {
  int lHeight = node->LHS->height;
  int rHeight = node->RHS->height;
  node->height = 1 + (lHeight > rHeight ? lHeight : rHeight);
  node->bias = lHeight - rHeight;
}

template <typename T>
void BinTree<T>::Replace(struct BinTreeNode<T> *before,
                         struct BinTreeNode<T> *after) {
  struct BinTreeNode<T> *parentNode = before->Parent;

  if (before == root) {
    root = after;
  } else if (parentNode->LHS == before) {
    parentNode->LHS = after;
  } else {
    parentNode->RHS = after;
  }

  after->Parent = parentNode;
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
    BalanceA(parent->LHS);
  } else {
    parent->RHS = newNode;
    BalanceA(parent->RHS);
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
  struct BinTreeNode<T> *deleteNode = searchNode(root, data);

  if (deleteNode == nullNode) {
    return false;
  }

  if (deleteNode->LHS == nullNode) {
    Replace(deleteNode, deleteNode->RHS);
    BalanceE(deleteNode->RHS);
    delete deleteNode;
  } else {
    struct BinTreeNode<T> *leftMaxNode = LeftMax(deleteNode);
    deleteNode->data = leftMaxNode->data;
    Replace(leftMaxNode, leftMaxNode->LHS);
    BalanceE(leftMaxNode->LHS);
    delete leftMaxNode;
  }
  return true;
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

//      node            LHS
//   LHS    Z   -->    X   node
//  X   Y                 Y    Z
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateR(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *LHS = node->LHS;
  struct BinTreeNode<T> *Y = node->LHS->RHS;

  struct BinTreeNode<T> *partitionRoot = LHS;

  node->LHS = Y;
  if (Y != nullNode) {
    Y->Parent = node;
  }

  partitionRoot->RHS = node;

  Replace(node, LHS);
  node->Parent = LHS;

  modHeight(partitionRoot->RHS);
  modHeight(partitionRoot);

  return partitionRoot;
}

//   node                   LHS
// W      RHS          node     RHS
//     LHS   Z  -->   W    X   Y   Z
//    X   Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateRL(struct BinTreeNode<T> *node) {
  RotateR(node->RHS);
  return RotateL(node);
}

//   node                RHS
//  X    RHS   -->   node   Z
//     Y    Z       X    Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateL(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *RHS = node->RHS;
  struct BinTreeNode<T> *Y = node->RHS->LHS;

  struct BinTreeNode<T> *partitionRoot = RHS;

  node->RHS = Y;
  if (Y != nullNode) {
    Y->Parent = node;
  }

  partitionRoot->LHS = node;
  Replace(node, RHS);
  node->Parent = RHS;

  modHeight(partitionRoot->LHS);
  modHeight(partitionRoot);

  return partitionRoot;
}

//       node            RHS
//   LHS      Z      LHS     node
//  W   RHS     --> W   X   Y    Z
//     X   Y
template <typename T>
struct BinTreeNode<T> *BinTree<T>::RotateLR(struct BinTreeNode<T> *node) {
  RotateL(node->LHS);
  return RotateR(node);
}

//--------------------
// balance
//--------------------

template <typename T>
void BinTree<T>::BalanceA(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *targetNode = node;

  while (targetNode->Parent != nullNode) {
    struct BinTreeNode<T> *parentNode = targetNode->Parent;
    int height = parentNode->height;

    // when target node is LHS
    if (parentNode->LHS == targetNode) {
      if (bias(parentNode) == 2) {

        parentNode = bias(parentNode->LHS) >= 0 ? RotateR(parentNode)
                                                : RotateLR(parentNode);
      } else {
        modHeight(parentNode);
      }
      // when target node is RHS
    } else {
      if (bias(parentNode) == -2) {
        parentNode = bias(parentNode->RHS) <= 0 ? RotateL(parentNode)
                                                : RotateRL(parentNode);
      } else {
        modHeight(parentNode);
      }
    }

    if (height == parentNode->height) {
      break;
    }

    targetNode = parentNode;
  }
}

template <typename T> void BinTree<T>::BalanceE(struct BinTreeNode<T> *node) {
  struct BinTreeNode<T> *targetNode = node;

  while (targetNode->Parent != nullNode) {
    struct BinTreeNode<T> *parentNode = targetNode->Parent;
    int height = parentNode->height;

    // when objective node is RHS
    if (parentNode->RHS == targetNode) {
      if (bias(parentNode) == 2) {

        parentNode = bias(parentNode->LHS) >= 0 ? RotateR(parentNode)
                                                : RotateLR(parentNode);
      } else {
        modHeight(parentNode);
      }
      // when objective node is LHS
    } else {
      if (bias(parentNode) == -2) {
        parentNode = bias(parentNode->RHS) <= 0 ? RotateL(parentNode)
                                                : RotateRL(parentNode);
      } else {
        modHeight(parentNode);
      }
    }

    if (height == parentNode->height) {
      break;
    }

    targetNode = parentNode;
  }
}

//--------------------
// debug
//--------------------

template <typename T> void BinTree<T>::graph() {

  ToDot();
  system("rm bintree.dot");
  system("eog bintree.png");
  system("rm bintree.png");
}

template <typename T> void BinTree<T>::graphDebug() {
  std::ofstream ofs("bintree.dot");

  ofs << "digraph BinTree {" << std::endl;
  ofs << "graph [centering=\"false\",ranksep=0.2,ordering=out,nodesep=0.5];"
      << std::endl;
  ofs << "node [shape=circle,width = 0.2, height = 0.2, margin = "
         "0.01];"
      << std::endl;

  std::queue<struct BinTreeNode<T> *> queue;
  queue.push(root);

  int nullCount = 0;

  while (!queue.empty() && root != nullNode) {
    struct BinTreeNode<T> *front = queue.front();
    queue.pop();

    ofs << front->data << "[label=\"" << front->data << "("
        << front->Parent->data << "," << front->height << "," << bias(front)
        << ")\"];" << std::endl;
    if (front != root) {
      ofs << front->data << " -> " << front->Parent->data << ";" << std::endl;
    }

    if (front->LHS != nullNode) {
      ofs << front->data << " -> " << front->LHS->data << ";" << std::endl;
      queue.push(front->LHS);
    } else {
      ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
          << std::endl;
      ofs << front->data << " -> "
          << "nullNode" << nullCount << ";" << std::endl;
      nullCount++;
    }

    if (front->RHS != nullNode) {
      ofs << front->data << " -> " << front->RHS->data << ";" << std::endl;
      queue.push(front->RHS);
    } else {
      ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
          << std::endl;
      ofs << front->data << " -> "
          << "nullNode" << nullCount << ";" << std::endl;
      nullCount++;
    }
  }

  ofs << "}" << std::endl;

  system("dot -Kdot -Tpng bintree.dot -obintree.png");
  system("rm bintree.dot");
  system("eog bintree.png");
  system("rm bintree.png");
}

template <typename T> void BinTree<T>::ToDot() {
  std::ofstream ofs("bintree.dot");

  ofs << "digraph BinTree {" << std::endl;
  ofs << "graph [centering=\"false\",ranksep=0.2,ordering=out,nodesep=0.5];"
      << std::endl;
  ofs << "node [shape=circle,width = 0.2, height = 0.2, margin = "
         "0.01];"
      << std::endl;

  std::queue<struct BinTreeNode<T> *> queue;
  queue.push(root);

  int nullCount = 0;

  while (!queue.empty() && root != nullNode) {
    struct BinTreeNode<T> *front = queue.front();
    queue.pop();

    ofs << front->data << "[label=\"" << front->data << "\"];" << std::endl;

    if (front->LHS != nullNode) {
      ofs << front->data << " -> " << front->LHS->data << ";" << std::endl;
      queue.push(front->LHS);
    } else {
      ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
          << std::endl;
      ofs << front->data << " -> "
          << "nullNode" << nullCount << "[style=invis];" << std::endl;
      nullCount++;
    }

    if (front->RHS != nullNode) {
      ofs << front->data << " -> " << front->RHS->data << ";" << std::endl;
      queue.push(front->RHS);
    } else {
      ofs << "nullNode" << nullCount << "[label=\"0\",style=invis];"
          << std::endl;
      ofs << front->data << " -> "
          << "nullNode" << nullCount << "[style=invis];" << std::endl;
      nullCount++;
    }
  }

  ofs << "}" << std::endl;

  system("dot -Kdot -Tpng bintree.dot -obintree.png");
}

template <typename T> void BinTree<T>::animation(std::string dir) {

  ToDot();
  system("rm bintree.dot");

  std::string moveQuery =
      "mv bintree.png " + dir + "/" + std::to_string(animationCount) + ".png";
  system(moveQuery.c_str());

  animationCount++;
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
      DumpNode(tmp);
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
  if (root == nullNode) {
    return true;
  }

  std::queue<struct BinTreeNode<T> *> queue;
  queue.push(root);

  while (!queue.empty()) {
    struct BinTreeNode<T> *tmp = queue.front();
    queue.pop();

    int tmpBias = bias(tmp);

    if (tmpBias <= -2 || 2 <= tmpBias) {
      DumpNode(tmp);
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

template <typename T> void BinTree<T>::DumpNode(struct BinTreeNode<T> *node) {
  if (node == nullNode) {
    std::cout << "nullNode" << std::endl;
    return;
  }
  std::cout << "data:" << node->data << ",height:" << node->height
            << ",bias:" << bias(node) << ",LHS:" << node->LHS->data
            << ",RHS:" << node->RHS->data << std::endl;

  if (node->LHS == nullNode) {
    std::cout << "LHS is nullNode" << std::endl;
  }
  if (node->RHS == nullNode) {
    std::cout << "RHS is nullNode" << std::endl;
  }
  if (node == root) {
    std::cout << "root node" << std::endl;
  }
}
