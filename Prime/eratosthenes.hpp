#include <cmath>
#include <vector>

//<denite-clipy>eratosthenes:list all prime number from 0 to n</denite-clipy>
// must include vector and cmath
void eratosthenes(std::vector<bool> &isPrime, long long n) {
  isPrime[0] = false;
  isPrime[1] = false;
  for (long long i = 2; i <= n; i++) {
    isPrime[i] = true;
  }

  long long p = 2;
  while (p < std::sqrt(n)) {
    isPrime[p] = true;
    for (long long i = p + 1; i <= n; i++) {
      if (i % p == 0) {
        isPrime[i] = false;
      }
    }

    p++;
    while (isPrime[p] == false) {
      p++;
    }
  }
}
