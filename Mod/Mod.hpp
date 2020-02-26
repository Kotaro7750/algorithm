
// a,b is positive natural number
long long gcd(long a, long b) {
  long long bigger = a >= b ? a : b;
  long long smaller = a >= b ? b : a;
  long long r = bigger % smaller;
  while (r != 0) {
    bigger = smaller;
    smaller = r;
    r = bigger % smaller;
  }

  return smaller;
}
