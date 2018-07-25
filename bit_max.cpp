#include <algorithm>
#include <vector>

int const MAXN = 100000;
std::vector<int> bit(MAXN+1);

// update bit[j] (j >= i) with max(bit[j], x)
void update(int i, int x) {
  while (i <= MAXN) {
    bit.at(i) = std::max(bit.at(i), x);
    i += i & -i;
  }
}

// get max bit[j] (0 <= j <= i)
int getmax(int i) {
  int s = 0;
  while (i>0) {
    s = std::max(bit.at(i), s);
    i -= i & -i;
  }
  return s;
}