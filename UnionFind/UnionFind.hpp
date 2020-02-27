#include <vector>

class UnionFind {
public:
  UnionFind(long long n);
  long long size(long long n);
  bool merge(long long a, long long b);
  long long root(long long a);
  bool isSame(long long a, long long b);

private:
  long long N;
  std::vector<long long> parentArr;
  std::vector<long long> sizeArr;
  std::vector<long long> rankArr;
};

UnionFind::UnionFind(long long n) {
  N = n;
  parentArr.resize(n);
  sizeArr.resize(n);
  rankArr.resize(n);

  for (long long i = 0; i < n; i++) {
    parentArr[i] = i;
    sizeArr[i] = 1;
    rankArr[i] = 0;
  }
}

long long UnionFind::size(long long a) { return sizeArr[root(a)]; }

bool UnionFind::merge(long long a, long long b) {
  long long root_a = root(a);
  long long root_b = root(b);

  if (root_a == root_b) {
    return false;
  }

  if (rankArr[root_a] < rankArr[root_b]) {
    parentArr[root_a] = root_b;
    sizeArr[root_b] += sizeArr[root_a];
  } else {
    parentArr[root_b] = root_a;
    sizeArr[root_a] += sizeArr[root_b];
    if (rankArr[root_a] == rankArr[root_b]) {
      rankArr[root_a]++;
    }
  }
  return true;
}

long long UnionFind::root(long long a) {
  long long tmp = a;
  while (tmp != parentArr[tmp]) {
    tmp = parentArr[tmp];
  }
  return parentArr[a] = tmp;
}

bool UnionFind::isSame(long long a, long long b) { return root(a) == root(b); }
