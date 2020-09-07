// Original: https://img.atcoder.jp/practice2/ac-library.zip

/*
 * Return sum of floor((A*i+B)/M) from i = 0 ... N-1
 */
long long floor_sum(long long n, long long m, long long a, long long b) {
  long long ans = 0;
  if (a >= m) {
    ans += (n - 1) * n * (a / m) / 2;
    a %= m;
  }
  if (b >= m) {
    ans += n * (b / m);
    b %= m;
  }

  long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
  if (y_max == 0) return ans;
  ans += (n - (x_max + a - 1) / a) * y_max;
  ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
  return ans;
}
