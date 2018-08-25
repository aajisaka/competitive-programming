#include<vector>

const int MAXN = 2*100000;
std::vector<int> bit(MAXN+1);

// return bit[0] + bit[1] + ... + bit[i]
int sum(int i) {
  int s = 0;
  while (i > 0) {
    s += bit.at(i);
    i -= i & -i;
  }
  return s;
}

// bit[i] += x
void add(int i, int x) {
  while (i <= MAXN) {
    bit.at(i) += x;
    i += i & -i;
  }
}

void reset() {
  for(int i=0; i<=MAXN; i++) {
    bit.at(i) = 0;
  }
}